#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	FILE *fp1,*fp2;
	int version,i;
	char ch;
	int arg_len=strlen(argv[1]);
	char line[10],linetest[10];
	if(argc>2)
	{
		printf("Too many arguments!\n");
	}
	else if(argc<2)
	{
		printf("Too few arguments!\n");
	}

	else
	{
		version=atoi(argv[1]);                                      //converting string to an integer

		if(version==0)
		{	
			//name detect
			fp1=fopen("log.txt","a+");   		            //log file to store the changes made i the test.txt file; opened in the append+ mode
			fp2=fopen("test.txt","r+");                         //test file that needs version control
			rewind(fp1);
			
			if(fgetc(fp1)=='#')
			{
				while(fgetc(fp1)!=EOF);
				fputs("#",fp1);                            
				fputs("\n",fp1);
				while(fgets(line,10,fp2)!=NULL)
				{
				fputs(line,fp1);                            //insert the new appended line in the log file
				}
				fputs("$",fp1);                             //$ signifies that recording the changes made in the test file has ended
				fputs("\n",fp1);              
				system("echo Version Commit!");
			}
			else						    //first commit
			{
				char str[5]="#\n";
				fputs(str,fp1);
				while(fgets(line,10,fp2)!=NULL)
				{
				fputs(line,fp1);
				}
				fputs("$",fp1);
				fputs("\n",fp1);
				system("echo First Commit!");
			}		
		}
		else
		{	
			//number detect
			int count=1;
			fp1=fopen("log.txt","a+");
			fp2=fopen("test.txt","w");
			if(version!=1)
			fgets(line,10,fp1);
			while(version!=count)                              //no. of versions is equal to no. of #
			{ 
			if(!fgets(line,10,fp1))
			break;
			if(line[0]=='#')
			count++;
			}
			if(version==count)
			{
				if(count==1) 				   //first version or the original file
				fgets(line,10,fp1);
				while(1)
				{
				fgets(line,10,fp1);
				if(line[0]!='$')
				fputs(line,fp2);
				else
				break;
				}
			}
		printf("Version detected!\n");
		}
		fclose(fp1);
		fclose(fp2);
	}
	return;
}

