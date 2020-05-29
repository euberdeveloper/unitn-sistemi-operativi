#include <stdio.h>
//#include <stdbool.h>
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

char* MESSAGE = "3 ciao.txt 23 23 23 23 23 23 come.txt 23 23 23 23 23 23 \\ciao\\come\\va.txt  2147483647 23121223 23 23 23 23";

 
int main(){
  
    time_t start_time = time(NULL);
    int data_file_number;
    char* TEST_MESSAGE = (char*) malloc (strlen(MESSAGE) + 1);
    strcpy(TEST_MESSAGE, MESSAGE);
    //printf("%s\n", TEST_MESSAGE);
    int number_of_files = 0;
    DATA_FILE* FILES = deserialize(TEST_MESSAGE, &number_of_files);
    char* matrix[1] = {"\\ciao\\come\\va.txt"};
    show_files(FILES, number_of_files, true, true, matrix, 1);
    //now i have all the data structure
    
    time_t end = time(NULL);
    printf("Elapsed time = %d\n", (int) (end - start_time));
    return 0;
}



