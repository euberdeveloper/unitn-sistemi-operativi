#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include  "R_functions.h"

char* MESSAGE = "3 ciao.txt 234 2345 23456 234567 2345678 23456789 come.txt 23 23 23 23 23 23 \\ciao\\come\\va.txt  2147 2312 23 23 23 23";

 



int main(){
  
    time_t start_time = time(NULL);
    //printf("%05d\n",2);

    

    
    char* TEST_MESSAGE = (char*) malloc (strlen(MESSAGE) + 1);
    strcpy(TEST_MESSAGE, MESSAGE);
    //printf("%s\n", TEST_MESSAGE);
    int number_of_files = 0;
    DATA_FILE* FILES = deserialize(TEST_MESSAGE, &number_of_files);
    char* hope = serialize(FILES, number_of_files);
    number_of_files = 0;
    printf("%s\n",hope);
    
    DATA_FILE* files_copy = deserialize(&hope[8], &number_of_files);

    char* matrix[1] = {"\\ciao\\come\\va.txt"};

    //show_files(files_copy, number_of_files, true, true, matrix, 1);
    //now i have all the data structure
      
    time_t end = time(NULL);
    printf("Elapsed time = %d\n", (int) (end - start_time));
    return 0;
}



