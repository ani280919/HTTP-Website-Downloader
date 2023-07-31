HTTP Downloader :
There are 3 separate programs for each of the step.
Files present :
1. Step1.c
2. Step2.c
3. Step3.c
4. input.txt [ as provided in assignment question where instead of 30 objects , I took 10 objects]
5. input2.txt [ self created from zootaxa.info - contains png,gif,jpg,jpeg . Total 11 objects|| Sometimes it takes bit of delay to download in that case please use input.txt]

Note1 : Each object link is separated by a space and a newline in the text files
Note2: Sometimes input2.txt faces too many requests and takes long time. Please use input.txt in that case


For Step 1 of the assignment:
---->COMPILE: gcc.step1.c
---->RUN: ./a.out <"provide the URL">

eg : ./a.out "https://images.unsplash.com/photo-1558981285-6f0c94958bb6?ixlib=rb-1.2.1&ixid=eyJhcHBfaWQiOjEyMDd9&auto=format&fit=crop&w=500&q=60"
Note : Please include the URL within "" (quotes).
/* Program outputs Response Status , Response Header , the name of the file with which the object is saved , no of bytes recieved for the object*/

Object saved as "test_2.extension"
--------------------------------------------------------------------------------------------------------------------------------------------------------


For Step 2 of the assignment:
--->COMPILE : gcc step2.c
--->RUN: ./a.out
--->OUTPUT: Input the filename to be opened : <filename.txt>
/* Program gives Response Status , Response Header, The name of the file with which the objects are saved , The no of bytes recieved for each object. 
It continues untill all the objects in the provided text file are fetched , after which Total Time to download all the objects are displayed*/

Each object is saved with the name "step2_<obj_no>.extension" { obj_no starts with 0}

------------------------------------------------------------------------------------------------------------------------------------------------------------


For Step 3 of the assignment:
--->COMPILE : gcc step3.c
--->RUN: ./a.out
--->OUTPUT: Input the filename to be opened : <filename.txt>
/* Program gives Response Status , Response Header, The name of the file with which the objects are saved , The no of bytes recieved for each object. 
It continues untill all the objects in the provided text file are fetched , after which Total Time to download all the objects are displayed*/

Each object is saved with the name "step3_<obj_no>.extension" {obj_no starts with 0}

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
PLAGIARISM STATEMENT <Include it in your readme> I certify that this assignment/report is my own work, based on my personal study and/or research and that I have acknowledged all material and sources used in its preparation, whether they be books, articles, reports, lecture notes, and any other kind of document, electronic or personal communication. I also certify that this assignment/report has not previously been submitted for assessment in any other course, except where specific permission has been granted from all course instructors involved, or at any other time in this course, and that I have not copied in part or whole or otherwise plagiarised the work of other students and/or persons. I pledge to uphold the principles of honesty and responsibility at CSE@IITH. In addition, I understand my responsibility to report honour violations by other students if I become aware of it.
Name of the student : Anwesha Kar
Roll No: cs21mtech12006

