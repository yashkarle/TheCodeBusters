#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node * createNode(int inode,char path[]);
void listdir(char *name, int level);
void insertToHash(int inode,char path[]);
int searchInHash(int inode,char path[]);


int i=1;
struct hash *hashTable = NULL;
  int eleCount = 0;

  struct node
  {
        int inode;
	char path[1024];
        struct node *next;
  };

  struct hash
  {
        struct node *head;
        int count;
  };
void listdir(char *name, int level)
{
int j,inod;
char tempo[256];
    struct list *head=NULL,*current,*temp;
    DIR *dir;
    struct dirent *entry;

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

           //printf("%d:[%s]\n",i++,entry->d_name);
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
        	    //printf("\t%d:%s\n", i++,entry->d_name);
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




  int searchInHash(int inode,char path[])
  {
        int hashIndex = inode % eleCount, flag = 0,val;
	char str[1024]="rm ";
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) 
	{
                //printf("NA\n");
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
			printf("Removed %s\n",path);
			break;
			case 2:
			strcat(str,myNode->path);
			system(str);
			printf("Removed %s\n",myNode->path);
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
	//printf("NA\n");
	return 0;
	}
	return 1;
  }
void display()
{
        struct node *myNode;
        int i;
        for (i = 0; i < eleCount; i++)
        {
                if (hashTable[i].count == 0)
                        continue;
                myNode = hashTable[i].head;
                if (!myNode)
                        continue;
                printf("\nIndex:%d\n", i);
                while (myNode != NULL) 
		{
                        printf("%d\n", myNode->inode);
                        myNode = myNode->next;
                }
        }
        return;
  }
int main(void)
{
    eleCount = 10;
    hashTable = (struct hash *)calloc(10, sizeof (struct hash));
    listdir(".", 0);
    //display();
    
    return 0;
}
//can be done for duplicate names
//can be done for same size
//check for non home directories
