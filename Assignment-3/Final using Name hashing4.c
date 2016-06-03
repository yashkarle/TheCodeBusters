#include <unistd.h>
#include <sys/types.h>
//dirent.h is used to access directories in the system
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pwd.h>

struct node * createNode(char fname[],char path[]);
void listdir(char *name, int level);
void insertToHash(char fname[],char path[]);
int searchInHash(char fname[],char path[]);


int i=1;
 struct hash *hashTable = NULL;
  int eleCount = 0;

//structure of node for chaining in hash
  struct node
  {
        char fname[256];
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
		    strcpy(tempo,name);
		    strcat(tempo,"/");
		    strcat(tempo,entry->d_name);
		    searchInHash(entry->d_name,tempo);
		    insertToHash(entry->d_name,tempo);
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

//hash table insertion
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



//searching in hash table
  int searchInHash(char fname[],char path[])
  {
        int hashIndex = fname[0] % eleCount, flag = 0,val;
	char str[1024]="rm ",ch;
        struct node *myNode;
	FILE *fp1,*fp2;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                return 0;
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
			//the merge files copies the content of second file into the first
			fp1=fopen(path,"a+");
			fp2=fopen(myNode->path,"r");
			while( ( ch = fgetc(fp2) ) != EOF )
      			fputc(ch,fp1);
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
    eleCount = 26;
    struct passwd *pw = getpwuid(getuid());

    char *homedir = pw->pw_dir;
    hashTable = (struct hash *)calloc(26, sizeof (struct hash));
    listdir(homedir, 0);
    
    return 0;
}
