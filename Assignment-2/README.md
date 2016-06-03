
GOAL:
Create a simple version control (svc) program called "svc".

DETAILS:
We have a text file that needs version control i.e., ability to revert back
to any previous version.  
- The text that is composed of one or more lines.
- Each line has a maximum character width of 10 characters (including newline).
- The total number of lines is 20.

The following operations are permitted:
1. Appending a new line at the end of the file.
2. Deleting any existing line.

Only one of the above operations can be done at a given time i.e., the user
can either append a line -or- delete a line. After each operation, the file
is commited using the svc. 

The usage of svc is the following
svc filename   : To commit
svc N          : Output Nth version of the file.

A sample flow is as follows:
1. Create a file test.txt
2. test.txt has the following line:
hello
3. Commit "svc test.txt" /* Version 0 */
4. Add another line:
world
5. Commit "svc test.txt" /* Version 1 */
6. Display version 1 "svc 1"
hello
world
7. Display version 0 "svc 0"
hello
8. Delete the line hello  and then run "svc test.txt"
9. Disp


The approach that we have used is as follows : 
We have a file test.txt that needs simple version control. For this we create another file called log.txt to record the different changes made in the test.txt file. In the log file # signifies that the different changes made in a particular version would now be recorded and $ signifies that these changes have been finished recording. So the following piece of code would get added to the log file.
For eg. we first add a line "hello" to test.txt. 
#
hello
$
We then commit this file using the command "./a.out test.txt". This is the original file. Now whatever changes we make in this file; all of them would get recorded in the log file.
For eg. if we append a line "world", code stored in the log file would be
#
hello
$
#
hello
world
$
The same process would apply for all the n lines that we might append at the end of the file.
Now suppose we want to delete the line "hello".
The log file would store 
#
world
$
The number of # in the log file would be equal to the number of versions.
Hence if we want to access the 3rd version we would go go on moving the file pointer till the no. of counts of # is equal to the version no. that we want to output. 
Then we copy all data from that # till the next $ in the test.txt file thus getting the required output version. Thus a screenshot of the current version which we commit gets added to the log file.
