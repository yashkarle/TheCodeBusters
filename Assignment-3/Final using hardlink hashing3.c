#include <unistd.h>
#include <sys/types.h>
//dirent.h is used to access directories in the system
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pwd.h>

struct node * createNode(int inode,char path[]);
void listdir(char *name, int level);
void insertToHash(int inode,char path[]);
int searchInHash(int inode,char path[]);


int i=1;
struct hash *hashTable = NULL;
  int eleCount = 0;

//structure of node for chaining in hash
  struct node
  {
        int inode;
	char path[1024];
        struct node *next;
  };

//hash table structure
  struct hash
  {
        struct node *head;
        int count;
  };


//recursively search all the directories
void listdir(char *name, int level)
{
    int j,inod;
    char tempo[256];
    struct list *head=NULL,*current,*temp;
    
    DIR *dir;//directory stream
    struct dirent *entry;//dirent structure provides with inode,type,size of files

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        
	if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);

            path[len] = 0;

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            listdir(path, level + 1);
        }

	  	else
		{   
		    inod=(int)entry->d_ino;
		    strcpy(tempo,name);
		    strcat(tempo,"/");
		    strcat(tempo,entry->d_name);
		    searchInHash(inod,tempo);
		    insertToHash(inod,tempo);
		}
    	} while (entry = readdir(dir));

    closedir(dir);
}

  struct node * createNode(int inode,char path[])
  {
        struct node *newnode;
        newnode = (struct node *)malloc(sizeof(struct node));
        newnode->inode = inode;
	strcpy(newnode->path,path);
        newnode->next = NULL;
        return newnode;
  }

//hash table insertion
  void insertToHash(int inode,char path[])
  {
        int hashIndex = inode % eleCount;
        struct node *newnode =  createNode(inode,path);

        if (!hashTable[hashIndex].head)
        {
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].count = 1;
                return;
        }

        newnode->next = (hashTable[hashIndex].head);

        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
        return;
  }



//searching in hash table
  int searchInHash(int inode,char path[])
  {
        int hashIndex = inode % eleCount, flag = 0,val;
	char str[1024]="rm ";
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) 
	{
                return 0;
        }
        while (myNode != NULL) 
	{
                if (myNode->inode == inode)
		{
                        printf("Key:%d\t%d\n", i++,myNode->inode);
			printf("Current Inode Path:%s\n",path);
			printf("Old Inode Path:%s\n",myNode->path);

	  		printf("1.Remove current file\n2.Remove old file\n3.Ignore\n");
			scanf("%d",&val);
			switch(val)
			{
			case 1:
			strcat(str,path);
			system(str);
			printf("Removed from %s\n",path);
			break;
			case 2:
			strcat(str,myNode->path);
			system(str);
			printf("Removed from %s\n",myNode->path);
			break;
			case 3:
			break;
			}
                        flag = 1;
                        break;
                }
                myNode = myNode->next;
        }
        if (!flag)
        {
	return 0;
	}
	return 1;
  }
int main(void)
{
struct passwd *pw = getpwuid(getuid());
char *homedir = pw->pw_dir;
    eleCount = 10;
    hashTable = (struct hash *)calloc(10, sizeof (struct hash));
    listdir(homedir, 0);
    return 0;
}
