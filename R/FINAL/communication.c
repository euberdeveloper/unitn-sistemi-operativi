#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include "R_functions_final.h"


typedef struct{
    char** paths;
    unsigned long long * sizes;
    int paths_sizes_size;
}P_INPUT;

typedef struct{
    int start;
    int end;
}RANGE;

typedef struct{
    char** files_paths;
    RANGE* ranges;
    int size_ranges_files; // they are the same size 
}Q_INPUT;



P_INPUT* get_P_input(DATA_FILE* files, int files_size, int number_of_P){
    int divide = files_size / number_of_P;
    int scarto = files_size % number_of_P;
    int data_file_to_alloc;
    int i,j;
    int next_file_index = 0;
    int p_index = 0;
    P_INPUT* ret_Ps = (P_INPUT*) malloc (sizeof(P_INPUT) * number_of_P);
    for (i = 1; i <= divide; i++){
        if (scarto != 0){
            data_file_to_alloc = divide + 1;
            scarto--;
        } else {
            data_file_to_alloc = divide;
        }
        
        ret_Ps[p_index].paths_sizes_size = data_file_to_alloc;
        ret_Ps[p_index].paths = (char**) malloc (sizeof(char*) * data_file_to_alloc);
        ret_Ps[p_index].sizes = (unsigned long long *) malloc (sizeof(unsigned long long) * data_file_to_alloc);
        for(j = 0; j < data_file_to_alloc; j++){
            asprintf(&ret_Ps[p_index].paths[j], "%s", files[j + next_file_index].path);
            ret_Ps[p_index].sizes[j] = files[j + next_file_index].size;
        }
        next_file_index += data_file_to_alloc;
        p_index++;
    }
    return ret_Ps;
};


Q_INPUT* get_q_input(P_INPUT* p, int number_of_q){
    Q_INPUT* ret_Qs = (Q_INPUT*) malloc (sizeof(Q_INPUT) * number_of_q);
    int i;
    int level = 1;
    for (i = 0; i < number_of_q; i++){
        ret_Qs[i].ranges = (RANGE*) malloc (sizeof(RANGE) * p->paths_sizes_size);
        ret_Qs[i].files_paths = (char**) malloc (sizeof(char*) * p->paths_sizes_size);
        int j;
        for (j = 0; j < p->paths_sizes_size; j++){
            asprintf(&ret_Qs[i].files_paths[j],"%s", p->paths[j]);
            unsigned long long curr_size = p->sizes[j];
            unsigned long long step = curr_size / number_of_q;
            ret_Qs[i].ranges[j].start = (level-1)*step;
            if(level == number_of_q){
                ret_Qs[i].ranges[j].end = curr_size - 1;
            } else {
                ret_Qs[i].ranges[j].end = level*step - 1;
            }
        }
        level++;
    }
    return ret_Qs;
}


void A_to_P (P_INPUT* p, int p_fd){
    int i;
    write(p_fd, &p->paths_sizes_size, sizeof(int));
    for (i = 0; i < p->paths_sizes_size; i++){
        int len = strlen(p->paths[i]);
        write(p_fd, &len, sizeof(int));
        write(p_fd, p->paths[i], len);
        write(p_fd, &p->sizes[i], sizeof(unsigned long long));
    }
}

void P_to_Q (Q_INPUT* q, int q_fd){
    int i;
    write(q_fd, &q->size_ranges_files, sizeof(int));
    for (i = 0; i < q->size_ranges_files; i++){
        int len = strlen(q->files_paths[i]);
        write(q_fd, &len , sizeof(int));
        write(q_fd, q->files_paths[i], strlen(q->files_paths[i]));
        write(q_fd, &q->ranges->start, sizeof(int));
        write(q_fd, &q->ranges->end, sizeof(int));
    }
}



void dealloc_P(P_INPUT* p, int number_of_p){
    int i;
    int j;
    for (j = 0; j < number_of_p; j++){
        for (i = 0; i < p[j].paths_sizes_size; i++){
            free(p[j].paths[i]);
        }
        free(p[j].paths);
        free(p[j].sizes);
    }
}

void dealloc_Q(Q_INPUT* q, int number_of_q){
    int i,j;
    for (j = 0; j < number_of_q; j++){
        for (i = 0; i < q[j].size_ranges_files; i++){
            free(q[j].files_paths[i]);
        }
        free(q[j].ranges);
        free(q[j].files_paths);
    }
}




int main(int argc, char **argv)
{
    time_t start = time(NULL);
    int i,j,k;
    int files_size = 0;
    DATA_FILE *files = get_files(&argv[1], argc - 1, &files_size, false);
    
    P_INPUT* p_s = get_P_input(files, files_size, 3);

    for (i = 0; i < 3; i++){
        printf("P%d possiede:\n", i);
        int j;
        for (j = 0; j < p_s[i].paths_sizes_size; j++){
            printf("\'%d\'--> '%s\n",j,p_s[i].paths[j]);
        }
        Q_INPUT* q_s = get_q_input(&p_s[i], 4);
        printf("P%d:\n", i);
        int z;
        for (z = 0; z < 4; z++){
            printf("Q%d:\n",z);
            for (k = 0; k < p_s[i].paths_sizes_size; k++){
                printf("file \'%s\':\n", q_s[z].files_paths[k]);
                printf("Read  from \'%d\' to \'%d\'\n", q_s[z].ranges[k].start, q_s[z].ranges[k].end);
            }
        }
       
    }
    
 
    dealloc_FILES(files, files_size);
    time_t end = time(NULL);
    printf("Elapsed time = %d ", (int)(end - start));
    printf("\nDONE\n");
    return 0;
}
