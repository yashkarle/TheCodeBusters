#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int command(char str[])
{
    if(strstr(str,"mkdir")!=NULL)
        return 1;
    else if(strcmp(str,"q")==0)
        return 99;
        else if(strstr(str,"cd")!=NULL)
        {
           return 2;
        }
        else if(strstr(str,"copy")!=NULL)
            return 4;
        else if(strstr(str,"create"))
            return 3;
       else if(strstr(str,"cat"))
        return 5;
        else if(strcmp(str,"ls")==0)
            return 6;
        else if(strstr(str,"delete")!=NULL)
            return 7;
}

int main()
{

FILE * fp,*fo;
fp=fopen("textfs.txt","r+");
char test[66],str[50],blk[5],dirname[10],pass[20],str1[20],extfile[50],intfile[50],ch,input[30],passcheck[20];
int bytes,c=5,block,n,i,ans,l,j,flag,k,m,jmp,arr[1000],num,start,end,fblock=21;
fgets(test,66,fp);
i=7;
j=0;
while(test[i]!='#'&&test[i]!='b')
{
  str[j++]=test[i++];
}
str[j]='\0';
block=atoi(str);
printf("block=%d\n",block);

i=16;
j=0;

while(test[i]!='#'&&test[i]!='f')
{

  str[j++]=test[i++];
}
str[j]='\0';
fblock=atoi(str);
printf("fblock=%d\n",fblock);

i=31;
j=0;

while(test[i]!='#'&&test[i]!='p')
{

  pass[j++]=test[i++];
}
pass[j]='\0';

//printf("password=%s\n",pass);

while(1)
{

gets(input);
n=command(input);


  switch(n)
  {
 case 1:
     printf("entered");                                               //Create Directory
     printf("c=%d",c);
     jmp=c;
     fseek(fp,jmp*66,SEEK_SET);
     fgets(test,66,fp);
     printf("%s",test);

     while(test[61]!='#')
     {
         i=61;j=0;
         while(test[i]!='#'&&test[i]!='\n')
             blk[j++]=test[i++];
blk[j]='\0';
printf("jmp=%s\n",blk);
            jmp=atoi(blk);
             printf("jmp=%d\n",jmp);
             fseek(fp,jmp*66,SEEK_SET);
             fgets(test,66,fp);
             printf("%s",test);
     }
     i=0;
     while(test[i]!='#')
        i++;
        printf("i=%d\n",i);

        j=6;
        k=0;
        while(input[j]!='\0')
            dirname[k++]=input[j++];

        dirname[k]='\0';


        sprintf(blk,"%d",block);
        l=strlen(dirname)+strlen(blk);

        if(l+2<=(60-i))
        {
        fseek(fp,jmp*66+i,SEEK_SET);
        fputs("/",fp);

         fputs(dirname,fp);
         fputs("-",fp);

          fputs(blk,fp);

         fseek(fp,66*block,SEEK_SET);
         fputs("d",fp);

            sprintf(str,"%d",c);
            fputs(str,fp);
           block++;
          printf("block1=%d\n",block);


        }

        else
        {

                fseek(fp,jmp*66+61,SEEK_SET);
                sprintf(blk,"%d",block);

                fputs(blk,fp);
                   i=0;
                   j=0;

                  while(test[i]!='/')
                  str1[j++]=test[i++];

                  str1[j]='\0';
                  printf("str=%s\n",str1);
                  fseek(fp,66*block,SEEK_SET);
                  block++;
                   sprintf(blk,"%d",block);
                  fputs(str1,fp);
                  fputs("/",fp);
                  fputs(str,fp);
                  fputs("-",fp);
                  fputs(blk,fp);

                 fseek(fp,66*block,SEEK_SET);
                 fputs("d",fp);
                 sprintf(str,"%d",c);
                 fputs(str,fp);


                  block++;
                 printf("block1=%d\n",block);


        }



    break;

 case 2:                                              //Change Directory
    bytes=66*c;
    fseek(fp,bytes,SEEK_SET);
     fgets(test,66,fp);
      printf("%s",test);
printf("input=%s",input);
j=3;
k=0;
        while(input[j]!='\0')
            dirname[k++]=input[j++];

        dirname[k]='\0';
        //printf("dirname=%s",dirname);

      i=0;
      j=0;
      flag=0;
      while(1)
      {
         if((test[i]=='#')&&test[61]!='#')
      {
              j=61;
              k=0;
              while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];

              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;

      }
      else if(test[i]!='#')
      {
          //printf("i=%d\n",i);
                if(test[i]=='/')
               j=0;
          else if(test[i]=='-')
          {
              str[j]='\0';
              if(strcmp(dirname,str)==0)
              {
                  printf("\ndirectory changed\n");
                  m=0;
                  k=i+1;
                  while(test[k]!='#'&&test[k]!='/'&&test[k]!='l')
                  {
                      blk[m]=test[k];
                      m++;
                      k++;
                  }

                  blk[m]='\0';
                  printf("blk=%s\n",blk);
                  c=atoi(blk);
                  //printf("c=%d\n",c);
                  fseek(fp,66*c,SEEK_SET);
                  fgets(str,66,fp);
                  printf("%s\n",str);
                  flag=1;

                  break;

              }

          }
          else
          {
            str[j]=test[i];
            j++;

          }

          i++;
      }
      else if((test[i]=='#')&&test[61]=='#')
      break;

      }


      if(flag==0)
        printf("\ndirectory does not exist\n");

      break;


case 3:                                           //Create File
    jmp=c;
     fseek(fp,jmp*66,SEEK_SET);
     fgets(test,66,fp);
     printf("%s",test);

     while(test[61]!='#')
     {
         i=61;j=0;
         while(test[i]!='#'&&test[i]!='\n')
             blk[j++]=test[i++];
blk[j]='\0';
printf("jmp=%s\n",blk);
            jmp=atoi(blk);
             printf("jmp=%d\n",jmp);
             fseek(fp,jmp*66,SEEK_SET);
             fgets(test,66,fp);
             printf("%s",test);
     }

     i=7;
     k=0;
     while(input[i]!='\0')
        str[k++]=input[i++];

     str[k]='\0';
     i=0;
     while(test[i]!='#')
        i++;


        sprintf(blk,"%d",block);
        l=strlen(str)+strlen(blk);

        if(l+2<=(60-i))
        {
        fseek(fp,jmp*66+i,SEEK_SET);
        fputs("/",fp);

         fputs(str,fp);
         fputs("-",fp);

         fputs(blk,fp);

         printf("Do you want to password protect\n");
         scanf("%d",&n);
         fseek(fp,66*block,SEEK_SET);
         fputs("f",fp);
        if(n==1)
         fputs("p",fp);
         else
            fputs("n",fp);
            fputs(".",fp);
            sprintf(str,"%d",c);
            fputs(str,fp);
            fputs(".",fp);


         block++;
         printf("block=%d\n",block);


        }

        else
        {

                fseek(fp,jmp*66+61,SEEK_SET);
                sprintf(blk,"%d",block);

                fputs(blk,fp);
                   i=0;
                   j=0;

                  while(test[i]!='/')
                  str1[j++]=test[i++];

                  str1[j]='\0';
                  printf("str=%s\n",str1);
                  fseek(fp,66*block,SEEK_SET);
                  block++;
                   sprintf(blk,"%d",block);
                  fputs(str1,fp);
                  fputs("/",fp);
                  fputs(str,fp);
                  fputs("-",fp);
                  fputs(blk,fp);

                   printf("Do you want to password protect\n");
                    scanf("%d",&n);
                 fseek(fp,66*block,SEEK_SET);
                 fputs("f",fp);
                  if(n==1)
                   fputs("p",fp);
                    else
                     fputs("n",fp);


                    fputs(".",fp);
                    sprintf(str,"%d",c);
                    fputs(str,fp);
                    fputs(".",fp);

                  block++;
                 printf("block=%d\n",block);


        }
break;

case 4:                                       //Copy

    fseek(fp,66,SEEK_SET);
    fgets(test,66,fp);
    //printf("str=%s",test);
    i=0;
    m=0;
    k=0;
    arr[m]=-1;
    while(1)
    {

         if((test[i]=='#')&&test[61]!='#')
         {
             j=61;
              k=0;
             while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];
              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;
              continue;
         }
         else if(test[i]!='#')
         {

              if(test[i]!=','&&test[i]!='l')
                str1[k++]=test[i++];
                else if(test[i]==','||test[i]=='l')
                {
                    str1[k]='\0';
                  //  printf("str=%s \t",str1);
                    num=atoi(str1);
                    arr[m++]=num;
                    arr[m]=-1;
                    k=0;
                    i++;
                }

         }
         else if((test[i]=='#')&&test[61]=='#')
            break;

    }


  i=5;
  k=0;
  while(input[i]!=' ')
    extfile[k++]=input[i++];

  extfile[k]='\0';

  printf("ext=%s",extfile);
    i++;
    k=0;
  while(input[i]!='\0')
    intfile[k++]=input[i++];

  intfile[k]='\0';

  printf("int=%s",intfile);




  fseek(fp,66*c,SEEK_SET);
  fgets(test,66,fp);
  printf("str=%s",test);
  flag=0;
  i=0;

   while(1)
  {
      if((test[i]=='#')&&test[61]!='#')
      {
              j=61;
              k=0;
              while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];

              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;

      }
      else if(test[i]!='#')
      {
          //printf("i=%d\n",i);
                if(test[i]=='/')
               j=0;
          else if(test[i]=='-')
          {
              str[j]='\0';
              if(strcmp(intfile,str)==0)
              {
                  printf("\nfound\n");
                  m=0;
                  k=i+1;
                  while(test[k]!='#'&&test[k]!='/'&&test[k]!='l')
                  {
                      blk[m]=test[k];
                      m++;
                      k++;
                  }

                  blk[m]='\0';
                  printf("blk=%s\n",blk);
                  jmp=atoi(blk);
                  //printf("c=%d\n",c);
                  fseek(fp,66*jmp,SEEK_SET);
                  fgets(str,66,fp);
                  printf("%s\n",str);
                  flag=1;

                  break;

              }

          }
          else
          {
            str[j]=test[i];
            j++;

          }

i++;
      }
      else if((test[i]=='#')&&test[61]=='#')
      break;
  }
  if(flag==0)
  {
    printf("not found\n");
    break;
  }
  m=0;
printf(" a[0]=%d\t",arr[0]);
flag=0;
  if(arr[m]!=-1)
    {
       start=arr[m++];
       end=arr[m++];
       sprintf(blk,"%d",fblock);
       str1[0]='\0';
       strcat(str1,"/");
       strcat(str1,blk);
       strcat(str1,"/");
       i=0;
       printf("str=%d\n",str);
       while(str[i]!='#')
          i++;
          fseek(fp,66*jmp+i,SEEK_SET);
       fputs(str1,fp);
       fseek(fp,start*66,SEEK_SET);
    }
    else
    {
       // printf("hello");
        flag=0;
        sprintf(blk,"%d",fblock);
        str1[0]='\0';
       strcat(str1,"/");
       strcat(str1,blk);
       strcat(str1,"/");
       i=0;
       while(str[i]!='#')
          i++;
          fseek(fp,66*jmp+i,SEEK_SET);
       fputs(str1,fp);
        fseek(fp,fblock*66,SEEK_SET);
        flag=1;
    }


fo=fopen(extfile,"r+");
i=0;
while((ch=fgetc(fo))!=EOF)
{


    if(flag==1)
    {
           if(ch=='\n')
            test[i]=' ';
            else
                test[i]=ch;
            i++;


        if(i==60)
        {
            test[i]='\0';
            i=0;
            strcat(test,"_$##");
            fprintf(fp,"%s\n",test);
            fblock++;
        }
    }
    else if(start<end)
    {
        if(ch=='\n')
            test[i]=' ';
            else
                test[i]=ch;
            i++;

        if(i==60)
        {
            test[i]='\0';
            i=0;
            strcat(test,"_$##");
            fprintf(fp,"%s\n",test);
            start++;
        }

    }
    else if(start==end)
    {
        if(ch=='\n')
            test[i]=' ';
            else
                test[i]=ch;
            i++;
        if(i==60)
        {
            test[i]='\0';
            i=0;


                  if(arr[m]!=-1)
                         {
                            sprintf(blk,"%d",arr[m]);
                            strcat(test,"_");
                            strcat(test,blk);
                            fprintf(fp,"%s\n",test);
                            fseek(fp,66*arr[m],SEEK_SET);
                            start=arr[m++];
                            end=arr[m++];
                        }
                        else if(arr[m]==-1)
                         {
                           flag=1;
                           sprintf(blk,"%d",fblock);
                           strcat(test,"_");
                           strcat(test,blk);
                           fprintf(fp,"%s\n",test);
                           fseek(fp,66*fblock,SEEK_SET);
                          }


        }


    }
}

if(i!=60)
{
    while(i<60)
    {
        test[i]='#';
        i++;
    }
    test[i]='\0';
    strcat(test,"_q##");
            fprintf(fp,"%s\n",test);
            if (flag==1)
                fblock++;
}
printf("fblock=%d",fblock);
fseek(fp,c*66,SEEK_SET);
fgets(test,66,fp);
printf("str=%s",test);

break;

case 5:                                                //Display

    fseek(fp,66*c,SEEK_SET);
    fgets(test,66,fp);
    printf("str=%s",test);
    flag=0;

    i=4;
    k=0;
    while(input[i]!='\0')
        intfile[k++]=input[i++];
    intfile[k]='\0';

    printf("intfile=%s",intfile);
    i=0;

    while(1)
  {
      if((test[i]=='#')&&test[61]!='#')
      {
              j=61;
              k=0;
              while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];

              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;

      }
      else if(test[i]!='#')
      {
          //printf("i=%d\n",i);
                if(test[i]=='/')
               j=0;
          else if(test[i]=='-')
          {
              str[j]='\0';
              if(strcmp(intfile,str)==0)
              {
                  printf("\nfound\n");
                  m=0;
                  k=i+1;
                  while(test[k]!='#'&&test[k]!='/'&&test[k]!='l')
                  {
                      blk[m]=test[k];
                      m++;
                      k++;
                  }

                  blk[m]='\0';
                  printf("blk=%s\n",blk);
                  jmp=atoi(blk);
                  //printf("c=%d\n",c);
                  fseek(fp,66*jmp,SEEK_SET);
                  fgets(str,66,fp);
                  printf("%s\n",str);
                  flag=1;

                  break;

              }

          }
          else
          {
            str[j]=test[i];
            j++;

          }

     i++;
      }
      else if((test[i]=='#')&&test[61]=='#')
      break;
  }
  if(flag==0)
  {
    printf("not found\n");
    break;
  }
  if(str[1]=='p')
  {
      printf("Password:");
      scanf("%s",passcheck);
      if(strcmp(passcheck,pass)!=0)
      {
          printf("Invalid Access\n");
          break;
      }
  }

i=6;
j=0;
while(str[i]!='/')
    str1[j++]=str[i++];
    str1[j]!='\0';

printf("str1=%s",str1);
    jmp=atoi(str1);
    printf("jmp=%d",jmp);
    fseek(fp,66*jmp,SEEK_SET);
    fgets(test,66,fp);
    printf("str=%s",test);
i=0;
while(1)
{
    if(i<60)
    {
        if(test[i]=='#'&&test[61]=='q')
            break;
        else
    printf("%c",test[i]);
    i++;
    }
    else
    {
        if(test[61]=='$')
        {
            jmp++;
            fseek(fp,jmp*66,SEEK_SET);
            fgets(test,66,fp);
            i=0;
        }
        else if(test[61]=='q')
            break;
    }
}



    break;

case 6:                                                      //Listing

    i=0;
      j=0;
      flag=0;
      fseek(fp,c*66,SEEK_SET);
      fgets(test,66,fp);
      if(test[2]=='#')
       {
           printf("empty\n");
      break;
       }
      while(1)
      {
         if((test[i]=='#')&&test[61]!='#')
      {
              j=61;
              k=0;
              while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];

              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;

      }
      else if(test[i]!='#')
      {


          //printf("i=%d\n",i);
                if(test[i]=='/')
               j=0;
          else if(test[i]=='-')
          {
              str[j]='\0';
              printf("%s\t",str);


              }


          else
          {
            str[j]=test[i];
            j++;

          }

          i++;
      }

      else if((test[i]=='#')&&test[61]=='#')
      break;
  }
        printf("\n");
         break;

case 7:                                                       //Delete
    fseek(fp,66*c,SEEK_SET);
    fgets(test,66,fp);
    printf("str=%s",test);
    flag=0;

    i=7;
    k=0;
    while(input[i]!='\0')
        intfile[k++]=input[i++];
    intfile[k]='\0';

    printf("intfile=%s",intfile);
    i=0;

    while(1)
  {
      if((test[i]=='#')&&test[61]!='#')
      {
              j=61;
              k=0;
              while(test[j]!='#'&&test[j]!='\n')
                str1[k++]=test[j++];

              str1[k]='\0';
              jmp=atoi(str1);
              fseek(fp,66*jmp,SEEK_SET);
              fgets(test,66,fp);
              i=0;

      }
      else if(test[i]!='#')
      {
          //printf("i=%d\n",i);
                if(test[i]=='/')
               j=0;
          else if(test[i]=='-')
          {
              str[j]='\0';
              if(strcmp(intfile,str)==0)
              {
                  printf("\nfound\n");
                  m=0;
                  k=i+1;
                  while(test[k]!='#'&&test[k]!='/'&&test[k]!='l')
                  {
                      blk[m]=test[k];
                      m++;
                      k++;
                  }

                  blk[m]='\0';
                  printf("blk=%s\n",blk);
                  jmp=atoi(blk);
                  //printf("c=%d\n",c);
                  fseek(fp,66*jmp,SEEK_SET);
                  fgets(str,66,fp);
                  printf("%s\n",str);
                  flag=1;

                  break;

              }

          }
          else
          {
            str[j]=test[i];
            j++;

          }

     i++;
      }
      else if((test[i]=='#')&&test[61]=='#')
      break;
  }
  if(flag==0)
  {
    printf("not found\n");
    break;
  }
  i=6;
  j=0;
while(str[i]!='/')
{
        str1[j++]=str[i++];
        str[i-1]='#';
}
str[i]='#';
    str1[j]!='\0';
    printf("file=%s\n",str);
    printf("str1=%s",str1);
    jmp=atoi(str1);
    printf("jmp=%d",jmp);

    fseek(fp,66*2,SEEK_SET);
    strcat(jmp,",");
    fputs(jmp,fp);
    fseek(fp,66*jmp,SEEK_SET);
    fgets(test,66,fp);
    printf("str=%s",test);

while(1)
{
    if(i<60)
    {
        test[i]='#';

    }
    else
    {
        fseek(fp,66*jmp,SEEK_SET);
        fputs(test,fp);
        if(test[61]=='$')
        {
            jmp++;
            fseek(fp,jmp*66,SEEK_SET);
            fgets(test,66,fp);
            i=0;
        }
          else if(test[61]=='q')
          {
          fseek(fp,66*2,SEEK_SET);
          fgets(str,66,fp);
          i=0;
          while(str[i]!='#')
            i++;
          fseek(fp,66*2+i,SEEK_SET);

          sprintf(str1,"%d",jmp);
          fputs(str1,fp);
            break;
    }
        else
        {
          fseek(fp,66*2,SEEK_SET);
          fgets(str,66,fp);
          i=0;
          while(str[i]!='#')
            i++;
          fseek(fp,66*2+i,SEEK_SET);

          sprintf(str1,"%d",jmp);
          strcat(str1,",");
          fputs(str1,fp);
           i=61;
           j=0;
           while(test[i]!='#'&&test[i]!='\n')
             str1[j++]=test[i++];
        }
    }
}

  break;
  }

if(n==99)
    break;

}
sprintf(blk,"%d",block);
    fseek(fp,7,SEEK_SET);
    fputs(blk,fp);

printf("f=%d",fblock);
    sprintf(blk,"%d",fblock);
    fseek(fp,16,SEEK_SET);
    fputs(blk,fp);
    fclose(fp);




}

