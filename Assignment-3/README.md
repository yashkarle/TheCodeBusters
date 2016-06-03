In hard drive duplication two approaches have been considered.

Files having same filenames are searched throughout the system.

Files having hardlinks with each other(same inode) are searched for throughout the system.

'dirent.h' provides an abstraction for file and directory access via functions like opendir,readdir.

As such duplicate files maybe very large in number hashing has been used for duplicate searching.

Files are searched and manipulation options(remove,merge) are provided.

------------------------------------------------------------------------------------------------------------------

Hardlink Duplication:

In this approach we are considering the duplicate files having the same inodes(hardlinked files).
For Instance we create a hardlink by following the below procedure:

=>ln abc.txt bcd.txt

->ln command is used for creating hardlinks.
->abc.txt should already be in the system.
->bcd.txt will be created in the system.
->Both would have exactly same data irrespective of any modifications.
->These files can be moved anywhere still the hardlinks remain.

'dirent.h' provides a structure dirent which provides us with the inode of the file.

The program lists these common inodes alongwith the paths of the files and provides an option to delete both files.
Merging isn't an option because the files have same content.

-------------------------------------------------------------------------------------------------------------------

Name Duplication:

In this approach we are considering the duplicate files having the same names in different directories.

'dirent.h' provides a structure dirent which provides us with the filename.

The program lists these same named files alongwith the paths of the files and provides an option to delete or merge the files.
In merging the data in the second file is copied into the first.

