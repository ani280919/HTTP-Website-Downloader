#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include<time.h>
#include<sys/time.h>
#include <string.h>
struct timeval  tv1, tv2;// for setting timers
char TYPE[20];
char name[]="test";

//Function reads HTTP status and displays it
int http_status(int sock){
    char c;
    char *type;
    char buff[1024]="",*ptr=buff+1;
    int bytes_received, status;
    printf("Begin Response ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("ReadHttpStatus");
            exit(1);
        }

        if((ptr[-1]=='\r')  && (*ptr=='\n' )) break;
        ptr++;
    }
    *ptr=0;
    ptr=buff+1;

    sscanf(ptr,"%*s %d ", &status);
    printf("\n%s\n",ptr);
    printf("End Response ..\n");
    return (bytes_received>0)?status:0;

}

//Function reads the HTTP Response and Parses it. *Displays in output
int http_header(int sock){
    char c;
    char *type;
    char *end;
    char buff[1024]="",*ptr=buff+4;
    int bytes_received, status;
    printf("HEADER starts ..\n");//parsing of HTTP HEADER starts
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("Error");
            exit(1);
        }
        if((ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&(ptr[-1]=='\r')  && (*ptr=='\n' )) break;
        ptr++;
    }
    *ptr=0;
    ptr=buff+4;
    printf("--%s--",ptr);
    type=strstr((ptr),"Content-Type:");
    type=type+14;
    type=strstr(type,"/");
    type++;
    int i=0,j=0,k=0;
    for(;i<strlen(type)&&type[i]!='\r';i++)
    {
	TYPE[j]=type[i];
	j++;
	}
    TYPE[j]='\0';// The type of the object is saved here after parsing Content-Type	
    if(bytes_received){
        ptr=strstr(ptr,"Content-Length:"); 
        if(ptr){
            sscanf(ptr,"%*s %d",&bytes_received);//stores the number of bytes recieved from the HTTP response
        }else
            bytes_received=-1; 
    }
    printf("HEADER ends ..\n");//parsing of HTTP header ends
    return  bytes_received ;
}


int main() 
{
    char line[200][200];//stores the input file object URL's
    char fname[20];
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;
    printf(" Input the filename to be opened : ");
    scanf("%s",fname);	
    fptr = fopen(fname, "r");
    while(fgets(line[i],200, fptr)) 
	{
        line[i][strlen(line[i]) - 2] = '\0';//each URL gets stored in array of characters
        i++;
    }
    tot = i;// gives total no of objects
    
    
    gettimeofday(&tv1, NULL);// sets timer to calculate download time
    
    int obj=0;
    char *url=line[obj]; //URL of first object stored here
    char domain[200];
    i=0;
    for( i=0;i<strlen(url);i++){
    if(url[i]=='/'  && url[i+1]=='/')
	break;
    }
    char *ps=url +i+2;
    printf("%s",ps);
    char *ptrr;
    int j=0;
    ptrr=strstr(ps,"/");
    char *path=ptrr+1;
    printf("\n path :%s\n",path);//path extracted from the URL

    i=0;
    while(ps[i]!='/'){
    domain[j]=ps[i];
    j++;i++;
    }

   domain[j]='\0';
   printf("Domain: %s:\n",domain);//domain name extracted from the URL
   
    int sock, bytes_received;  
    char send_data[1024],recv_data[1024], *p;
    struct sockaddr_in server_addr;
    struct hostent *ip;


    ip = gethostbyname(domain);//to get address of the domain
    if (ip == NULL){
       herror("gethostbyname");
       exit(1);
    }
    
    //only 1 socket created for Persistent HTTP
    if ((sock = socket(AF_INET, SOCK_STREAM, 0))== -1){
       perror("Socket");
       exit(1);
    }
    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(80);
    server_addr.sin_addr = *((struct in_addr *)ip->h_addr);
    bzero(&(server_addr.sin_zero),8); 
    
    //Connecting to server
    printf("Connecting ...\n");
    if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
       perror("Connect");
       exit(1); 
    }
    
    //Now we send data as Non-Persistent GET request to the server
    printf("Sending data ...\n");
    gettimeofday(&tv1, NULL);// Now we set the timer after creation of the TCP socket and before sending of the GET Request
    for(obj=0;obj<tot;obj++){
    char *url=line[obj]; //each URL stored here
    char domain[200];
    int i=0;
    for( i=0;i<strlen(url);i++){
    if(url[i]=='/'  && url[i+1]=='/')
	break;
    }
    char *ps=url +i+2;
    printf("%s",ps);
    char *ptrr;
    int j=0;
    ptrr=strstr(ps,"/");
    char *path=ptrr+1;
    printf("\n path :%s\n",path);//path extracted from the URL

    i=0;
    while(ps[i]!='/'){
    domain[j]=ps[i];
    j++;i++;
    }
   domain[j]='\0';
   printf("Domain: %s:\n",domain);//domain name extracted from the URL
   
   //Now we send data as Persistent GET request to the server
   snprintf(send_data, sizeof(send_data), "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, domain);
    if(send(sock, send_data, strlen(send_data), 0)==-1){
        perror("send");
        exit(2); 
    }
    printf("Data sent.\n");  

    //Now we have to receive the HTTP response
    printf("Recieving data...\n\n");
    int len;
    if(http_status(sock) && (len=http_header(sock))){
        int bytes=0;
        int i=2;     
        snprintf(name,20, "step3_%d", obj);
        strcat(name,".");
        strcat(name,TYPE);
        printf("\n\n--@@@@**File created as %s**@@@@--\n",name);//object file name created based on type of it
        FILE* fd=fopen(name,"wb");
        printf("Saving data ...\n\n");
        
        
     //File now read to store the recieved bytes
        while(bytes_received = recv(sock, recv_data, 1024, 0)){
            if(bytes_received==-1){
                perror("recieve");
                exit(3);
            }
        fwrite(recv_data,1,bytes_received,fd);
            bytes+=bytes_received;
            printf("Bytes recieved: %d\n",bytes);
            if(bytes==len)
            break;
        }
        fclose(fd);// File closed
    }
    printf("\n\nDone.\n\n");
    }
    gettimeofday(&tv2, NULL);// timer stopped here as all the objects has been downloaded
    printf ("Total time = %f seconds\n",(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));
    
    close(sock);// TCP connection is closed at the end as it is persistent HTTP
    return 0;
}
