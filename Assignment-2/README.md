
In hard drive duplication two approaches have been considered.


Files having same filenames are searched throughout the system.


Files having hardlinks with each other(sam inode) are searched for throughout the system.


#include<dirent.h> provides an abstraction for file and directory access via functions like opendir,readdir.


As such duplicate files maybe very large in number hashing has been used for duplicate searching.


Files are searched and manipulation options(remove,merge) are provided.
