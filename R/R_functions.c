#include "R_functions.h"
#include <math.h>

DATA_FILE* deserialize(char* msg, int* result_size){
    char* iterator;
    iterator = strtok(msg, SPACE);
    sscanf(iterator ,"%d ", result_size);
    DATA_FILE* FILES = malloc ((*result_size) * (sizeof *FILES));
    int j = 0;
    int z = 0;
    for (j = 0; j < (*result_size); j++){
        int i;
        for(i = 0; i < 7; i++){
            switch (i)
            {
                case 0:{
                    if(z == 0){iterator = strtok(NULL, " ");z++;} 
                    int path_size = strlen(iterator);
                    FILES[j].path = (char*) malloc (path_size * sizeof(char));
                    strcpy(FILES[j].path, iterator);
                    break;
                }
                case 1:{
                    sscanf(iterator, "%d", &FILES[j].data_info.alpha_upper);
                    break;
                }
                case 2:{
                    sscanf(iterator, "%d", &FILES[j].data_info.alpha_over);
                    break;
                }
                case 3:{
                    sscanf(iterator, "%d", &FILES[j].data_info.digit);
                    break;
                }
                case 4:{
                    sscanf(iterator, "%d", &FILES[j].data_info.punct);
                    break;
                }
                case 5:{
                    sscanf(iterator, "%d", &FILES[j].data_info.space);
                    break;
                }
                case 6:{
                    sscanf(iterator, "%d", &FILES[j].data_info.other);
                    break;
                }
            }       
            iterator = strtok(NULL, " ");
        }    
    }
    return FILES;
}

int total_letter_from_file(DATA_FILE* file){
    return (file->data_info.alpha_over + file->data_info.alpha_upper + file->data_info.digit + file->data_info.punct + file->data_info.space + file->data_info.other);
}

char* base_name(const char* path){
    int lim_dx = strlen(path);
    int lim_sx;
    int i;
    for (i = lim_dx; i > 0; i--){
        if (path[i - 1] == '\\'){
            lim_sx = i;
            break;
        }
    }

    char* ret = (char*) malloc ((lim_dx - lim_sx) * sizeof(char) + 1);
    for (i = lim_sx; i < lim_dx; i++){
        ret[i - lim_sx] = path[i];
    }
    ret[lim_dx - lim_sx + 1] = '\0';
    return ret;
}


int print_file(DATA_FILE* file, bool case_sensitive, bool percentage){
    long long int tot = total_letter_from_file(file);
   // printf("tot = %d\n", tot);
   if(percentage){
        printf("--------------------------------------------------\n");//50
        printf("%-50s|\n", base_name(file->path));
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("%-18s|", "       Type");
        printf("%-10s |", "  Quantity  ");
        printf("%-17s|\n", "   Percentage");
        printf("--------------------------------------------------\n");
        fflush(stdout);
        if(case_sensitive){
            printf("Alpha_upper       | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper,fabs((float) ((float)file->data_info.alpha_over / (float)tot) * 100.0), "%");
            printf("--------------------------------------------------\n");
            printf("Aplha_over        | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_over,fabs((float) ((float)file->data_info.alpha_over / (float)tot) * 100.0), "%");
            printf("--------------------------------------------------\n");
        } else {
            printf("Alpha             | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper + file->data_info.alpha_over, fabs((float) (((float)(file->data_info.alpha_upper + file->data_info.alpha_over)) / (float)tot) * 100.0), "%");
            printf("--------------------------------------------------\n");
        }
        printf("Digit             | %-12d|      %-7.2f%s   |\n", file->data_info.digit, fabs((float) ((float)file->data_info.digit / (float)tot) * 100.0), "%");
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Punct             | %-12d|      %-7.2f%s   |\n", file->data_info.punct, fabs((float) ((float)file->data_info.punct / (float)tot) * 100.0), "%");
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Space             | %-12d|      %-7.2f%s   |\n", file->data_info.space, fabs((float) ((float)file->data_info.space / (float)tot) * 100.0), "%");
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Other             | %-12d|      %-7.2f%s   |\n", file->data_info.other, fabs((float) ((float)file->data_info.other / (float)tot) * 100.0), "%");
        printf("--------------------------------------------------\n");
        fflush(stdout);
    } else {
        printf("--------------------------------------------------\n");//50
        printf("%-50s|\n", base_name(file->path));
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("%-18s|", "       Type");
        printf("%-30s |\n", "  Quantity  ");
        printf("--------------------------------------------------\n");
        if(case_sensitive){
            printf("Alpha_upper       | %-30d|\n", file->data_info.alpha_upper);
            printf("--------------------------------------------------\n");
            printf("Aplha_over        | %-30d|\n", file->data_info.alpha_over);
            printf("--------------------------------------------------\n");
        } else {
            printf("Alpha             | %-30d|\n", file->data_info.alpha_upper + file->data_info.alpha_over);
            printf("--------------------------------------------------\n");
        }
        printf("Digit             | %-30d|\n", file->data_info.digit);
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Punct             | %-30d|\n", file->data_info.punct);
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Space             | %-30d|\n", file->data_info.space);
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("Other             | %-30d|\n", file->data_info.other);
        printf("--------------------------------------------------\n");
        fflush(stdout);

    }
  
    return 0;
}

int show_files(DATA_FILE* files, int number_of_files, bool case_sensitive, bool percentage, char** files_names, int size_file_names){
    int i;
    if (files_names == NULL){
        for(i = 0; i < number_of_files; i++){
            print_file(&files[i], case_sensitive, percentage);
            printf("\n");
            fflush(stdout);
        }
    } else {
        for (i = 0; i < size_file_names; i++){
            int j;
            for(j = 0; j < number_of_files; j++){
                if(strcmp(files_names[i], files[j].path) == 0){
                    print_file(&files[j], case_sensitive, percentage);
                    printf("\n");
                    fflush(stdout);
                    break;
                }
            }
        }
    }
}