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
#include "R_functions.h"

char* MESSAGE = "3 ciao.txt 234 2345 23456 234567 2345678 23456789 come.txt 23 23 23 23 23 23 \\ciao\\come\\va.txt  2147 2312 23 23 23 23";

 






int main(){

    time_t start_time = time(NULL);
    //printf("%05d\n",2);

    int n = 2000;
    DATA_FILE* FILES = malloc (n * (sizeof *FILES));
    int i = 0;
    for(i = 0; i < n; i++){
        FILES[i].path = "\\ciao";
        FILES[i].data_info.alpha_over = i;
        FILES[i].data_info.alpha_upper = i;
        FILES[i].data_info.digit = i;
        FILES[i].data_info.space = i;
        FILES[i].data_info.other = i;
        FILES[i].data_info.punct = i;
    }

    //printf("%s", FILE_to_string(FILES[0]));
    
    char * myfifo = "/tmp/myfifo";
    int fd = -1;
    do{
        fd = open(myfifo, O_WRONLY);
    } while(fd == -1);
      
    char* serialized = serialize(FILES, n);
    //printf("serialized = \n%s\n", serialized);
    int len = strlen(serialized);

    int curr_len = snprintf(NULL, 0 , "%d", len);
    char * ret = (char*) malloc(curr_len + 1);
    snprintf(ret , curr_len + 1, "%d ", len);

    
    write(fd, serialized, len);
    printf("msg = %d\n", len);
    time_t end = time(NULL);
    close(fd);
    printf("Elapsed time = %d\n", (int) (end - start_time));
    return 0;
}

/*
char* old_serialize(DATA_FILE* files, int files_size){
    printf("Serialization...");
    int curr_len = snprintf(NULL, 0 , "%d", files_size);
    char * ret = (char*) malloc(curr_len + 2);
    snprintf(ret , curr_len + 2, "%d ", files_size);
    int next_increase;
    int index;
    int magic = 1;
    //sleep(10);
    for (index = 0; index < files_size; index++){
        
        next_increase = strlen(files[index].path);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        strcat(ret, files[index].path);
        ret[curr_len + magic] = ' ';
        magic++;

        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.alpha_upper);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.alpha_upper);
        ret[curr_len + magic] = ' ';
        magic++;


        
       
        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.alpha_over);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.alpha_over);
        ret[curr_len + magic] = ' ';
        magic++;


        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.digit);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.digit);
        ret[curr_len + magic] = ' ';
        magic++;


        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.punct);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.punct);
        ret[curr_len + magic] = ' ';
        magic++;


        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.space);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.space);
        ret[curr_len + magic] = ' ';
        magic++;


        next_increase = snprintf(NULL, 0 , "%d", files[index].data_info.other);
        curr_len += next_increase;
        do{
            ret = (char*) realloc(ret, curr_len * sizeof(char) + magic);    
        }while(ret == NULL);
        snprintf(&ret[curr_len - next_increase + magic] , next_increase + magic, "%d", files[index].data_info.other);
        ret[curr_len + magic] = ' ';
        magic++;

		printf("%s\n\n", ret);
       // sleep(0.5);
        
    }

    int ret_len = strlen(ret);
    char* true_ret;
    do{true_ret = (char*) malloc (ret_len + 9);
    }while (true_ret == NULL);
    
    sprintf(true_ret, "%08d", (int)ret_len);
    true_ret[8] = ' ';
    true_ret = (char*) realloc(true_ret, ret_len + 9);
    strcat(true_ret, ret);
    free(ret);
    printf("Done\n");
    return true_ret;
}


*/

