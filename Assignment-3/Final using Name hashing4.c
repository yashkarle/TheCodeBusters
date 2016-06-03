#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct node * createNode(char fname[],char path[]);
void listdir(char *name, int level);
void insertToHash(char fname[],char path[]);
void searchInHash(char fname[],char path[]);


int i=1;
 struct hash *hashTable = NULL;
  int eleCount = 0;

  struct node
  {
        char fname[256];
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
		    strcpy(tempo,name);
		    strcat(tempo,"/");
		    strcat(tempo,entry->d_name);
		    searchInHash(entry->d_name,tempo);
		    insertToHash(entry->d_name,tempo);
        	    //printf("\t%d:%s\n", i++,entry->d_name);
		}
    	} while (entry = readdir(dir));

    closedir(dir);
}

 

  struct node * createNode(char fname[],char path[])
  {
        struct node *newnode;
        newnode = (struct node *)malloc(sizeof(struct node));
        strcpy(newnode->fname,fname);
	strcpy(newnode->path,path);
        newnode->next = NULL;
        return newnode;
  }


  void insertToHash(char fname[],char path[])
  {
        int hashIndex = fname[0] % eleCount;
        struct node *newnode =  createNode(fname,path);

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




  void searchInHash(char fname[],char path[])
  {
        int hashIndex = fname[0] % eleCount, flag = 0,val;
	char str[1024]="rm ";
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                //printf("NA\n");
                return;
        }
        while (myNode != NULL) {
                if (!strcmp(myNode->fname,fname)) {
                        printf("Key  %d: %s\n",i++,myNode->fname);
			printf("Current Inode Path:%s\n",path);
			printf("Old Inode Path    :%s\n\n",myNode->path);

	  		printf("1.Remove both files\n2.Merge files\n3.Ignore\n");
			scanf("%d",&val);
			switch(val)
			{
			case 1:
			strcat(str,path);
			system(str);
			printf("Removed %s\n",path);
			strcat(str,myNode->path);
			system(str);
			printf("Removed %s\n",myNode->path);
			break;
			case 2:
			//file operations file merging
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
                //printf("NA\n");
        return;
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
                printf("\nIndex:%c\n",myNode->fname[0]);
                printf("Name \n");
                printf("-----\n");
                while (myNode != NULL)
                {
                        printf("%s\n", myNode->fname);
                        myNode = myNode->next;
                }
        }
        return;
  }
int main(void)
{
    eleCount = 2;
    hashTable = (struct hash *)calloc(5, sizeof (struct hash));
    listdir("..", 0);
    //display();
    
    return 0;
}
