Mr. Ramesh, programmer by profession is very obsessed with his room partner Mr. Suresh.  Suresh leaves no opportunity to break into and check out important and private files of Ramesh. One fine day Ramesh decides to implement his own file system Textfs that could store important files without revealing much information about them. Textfs will be a text based file system meaning all the data regarding contents of file system(meta-data) and the actual data of files will go in a single text file. The only principle that this file system is based on is - simplicity.

As the only factor under consideration is simplicity and not efficiency he decides to write a user mode command line application. This application has following major goals :

1.  Create a new file (create command)

2. Copy content of external files into these newly created files (copy command)

3.  Print contents of internal files (echo command)

4. Delete existing file (delete command)

5. List all files (ls command)

Again in order to keep things simple he agrees on some limitations:

1. Application will only create/copy/print *text* files

2. Application will only allow copying contents from external files(eg : /usr/readme.txt can be copied to readme.txt created by the application); it won't allow editing of contents.

3. Application will act as a command interpreter and accept only five commands create, copy, echo, ls  and delete with relevant parameters ; all text files directly go into Textfs without any folder structure.

4. Textfs will store all the contents inside a single file meaning the minimal super block, the minimal inode list and the storage block will all be placed inside dynamically increasing text file.

Textfs will allow Ramesh to hide all private text files unless and until Suresh gets hold of the application.

Please help Ramesh in designing and implementing this file system.

You are free to standard super block - inode list - data block design or any other design as you wish. You are free to choose any method for storing data blocks only constraint being simplicity.

(NOTE : Standard super block and inode list will have hundreds of fields but we are only concerned about a few here. It is advisable not to look at these structures and design your own from scratch; marks will be allotted to design as a whole and not individual efficient algorithms. Also we are nowhere concerned about security and this is in no way related to cryptography- the science of data scrambling. As you design this system you will automatically realize how it hides the text files beneath Textfs) .



