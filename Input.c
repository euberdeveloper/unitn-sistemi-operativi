#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "Input.h"
#include <fcntl.h>

#define print_error(msg)\
         perror(msg); exit (EXIT_FAILURE);


typedef struct
{
 long           d_ino;
 off_t          d_off;
 unsigned short d_reclen;
 char           d_name[];
}linux_dirent;



int nread;
int fd;

int main(int argc, char** argv)
{
  open_folder(argv[1]);
  return(0);
}

void open_folder(char* folder) {
  int BUF_SIZE = 1024, bufpos, i = 0;
  char** copia = (char**)malloc(sizeof(char*));
  char buffer[BUF_SIZE];
  linux_dirent *d;

  fd = open(folder, O_RDONLY | O_DIRECTORY);
  if (fd == -1)
  {
    print_error("open");
  }
  else
  {
   for (;;)
   {
    nread = syscall(SYS_getdents, fd, buffer,BUF_SIZE);
    if (nread == -1)
    {
     print_error("getdents");
    }
     else if (nread == 0)
    {
     break;
    }
     printf("---opening folder---\n");
     printf("\nfile name\n");
     printf("--------------------\n");

     for (bufpos = 0; bufpos < nread;)
     {
//      fd = open(d->d_name, O_RDONLY | O_DIRECTORY);
//      if (fd == -1)
//      {
//       print_error("open");
//       copia = (char**)realloc(copia, sizeof(char*)*(i+1));
//       d = (linux_dirent *) (buffer + bufpos);
//       if (strcmp(d->d_name,".") !=0 && strcmp(d->d_name,"..")!=0)
//       {
//        asprintf(&copia[i], "%s", d->d_name);
//        printf("%s\n", copia[i]);
//       }
//       }
//       else if (fd == 0)
//       {
//        open_folder(d->d_name);
//       }
      copia = (char**)realloc(copia, sizeof(char*)*(i+1));
      d = (linux_dirent *) (buffer + bufpos);
      if (strcmp(d->d_name,".") !=0 && strcmp(d->d_name,"..")!=0)
      {
       asprintf(&copia[i], "%s", d->d_name);
       printf("%s\n", copia[i]);
      }
   bufpos += d->d_reclen;
   i++;
  }
 }
}
}
