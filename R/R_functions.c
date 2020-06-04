#include "R_functions.h"
#include <math.h>

DATA_FILE* deserialize(char* msg, int* result_size){
    printf("Deserialization...");
    fflush(stdout);
    char* iterator;
    iterator = strtok(msg, SPACE);
	//iterator = strtok(NULL,SPACE);
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
                    sscanf(iterator, "%d", &FILES[j].data_info.alpha_lower);
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
    printf("Done\n");
    fflush(stdout);
    return FILES;
}

int total_letter_from_file(DATA_FILE* file){
    return (file->data_info.alpha_lower + file->data_info.alpha_upper + file->data_info.digit + file->data_info.punct + file->data_info.space + file->data_info.other);
}





int print_file(DATA_FILE* file, bool case_sensitive, bool percentage){
    unsigned long  tot = total_letter_from_file(file);
   // printf("tot = %d\n", tot);
   if(percentage){
        printf("--------------------------------------------------\n");//50
        printf("%-50s|\n", basename(file->path));
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("%-18s|", "       Type");
        printf("%-10s |", "  Quantity  ");
        printf("%-17s|\n", "   Percentage");
        printf("--------------------------------------------------\n");
        fflush(stdout);
        if(case_sensitive){
            printf("Alpha_upper       | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper,fabs((float) ((float)file->data_info.alpha_lower / (float)tot) * 100.0), "%");
            printf("--------------------------------------------------\n");
            printf("Aplha_over        | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_lower,fabs((float) ((float)file->data_info.alpha_lower / (float)tot) * 100.0), "%");
            printf("--------------------------------------------------\n");
        } else {
            printf("Alpha             | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper + file->data_info.alpha_lower, fabs((float) (((float)(file->data_info.alpha_upper + file->data_info.alpha_lower)) / (float)tot) * 100.0), "%");
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
        printf("%-50s|\n", basename(file->path));
        printf("--------------------------------------------------\n");
        fflush(stdout);
        printf("%-18s|", "       Type");
        printf("%-30s |\n", "  Quantity  ");
        printf("--------------------------------------------------\n");
        if(case_sensitive){
            printf("Alpha_upper       | %-30d|\n", file->data_info.alpha_upper);
            printf("--------------------------------------------------\n");
            printf("Aplha_over        | %-30d|\n", file->data_info.alpha_lower);
            printf("--------------------------------------------------\n");
        } else {
            printf("Alpha             | %-30d|\n", file->data_info.alpha_upper + file->data_info.alpha_lower);
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
    return 0;
}

char* FILE_to_string(const DATA_FILE f){
    size_t len = 0;
    len = snprintf (NULL, 0, " %s %d %d %d %d %d %d", f.path, f.data_info.alpha_upper, f.data_info.alpha_lower, f.data_info.digit, f.data_info.punct, f.data_info.space, f.data_info.other);
    char *ret = calloc (1, sizeof *ret * len + 1);
    snprintf (ret, len + 1, " %s %d %d %d %d %d %d", f.path, f.data_info.alpha_upper, f.data_info.alpha_lower, f.data_info.digit, f.data_info.punct, f.data_info.space, f.data_info.other);
    return ret;
}

char* serialize(DATA_FILE* files, int files_size){
    printf("Serialization...");
    int curr_len = snprintf(NULL, 0 , "%d", files_size);
    char * ret = (char*) malloc(curr_len + 1);
    snprintf(ret , curr_len + 1, "%d", files_size);
    int index;
    int current_string_index = strlen(ret);
    int max_size = current_string_index;
    for (index = 0; index < files_size; index++){
        //2 for
        //1 per len
        //1 per strcat
        char* file_index_string = FILE_to_string(files[index]);
        int increment = strlen(file_index_string);
        ret = (char*)realloc(ret, sizeof(char) * (current_string_index + increment + 2));
        strcat(ret, file_index_string);
        current_string_index += increment;
    }

    int ret_len = strlen(ret);
    char* true_ret;
    true_ret = (char*) malloc (ret_len + 9);
    
    
    sprintf(true_ret, "%08d", (int)ret_len);
    //true_ret[8] = ' ';
    true_ret = (char*) realloc(true_ret, ret_len + 9);
    strcat(true_ret, ret);
    free(ret);
    printf("Done\n");
    return true_ret;
}

bool ends_with_txt(char* str){
    return (strcmp(&str[strlen(str) - 4], TXT) == 0);
}

void init_zero(DATA_FILE* file){
    file->data_info.alpha_lower = 0;
    file->data_info.alpha_upper = 0;
    file->data_info.digit = 0;
    file->data_info.other = 0;
    file->data_info.punct = 0;
    file->data_info.space = 0;
}

void visit_recursive(char *name, int mode, DATA_FILE* files, int* counter){
    linux_dirent *current_dir;
    int nread;
    int bpos;
    int fd;
    int fd_2;
    char buf[BUF_SIZE];
    bool is_dir = true;
    fd = open(name, O_RDONLY | O_DIRECTORY);
    if (fd == -1){
        printf("'%s' is not a directory\n", name);
        return;
    }
    while (is_dir){   
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == 0){
            is_dir = false;
        }
        for (bpos = 0; bpos < nread;){
            current_dir = (linux_dirent *)(buf + bpos);
            if (strcmp(current_dir->d_name, ".") != 0 && strcmp(current_dir->d_name, "..") != 0){
                char* path;
                asprintf(&path,"%s/%s", name, current_dir->d_name);
                fd_2 = open(path, O_RDONLY | O_DIRECTORY);
                if (fd_2 != -1){   
                    close(fd_2);
                    visit_recursive(path,mode,files,counter);
                }
                if (ends_with_txt(path)){
                    if (mode == WRITE_MODE){
                        asprintf(&files[*counter].path, "%s", path);
                        init_zero(&files[*counter]);   
                        //
                        struct stat s;
                        stat(files[*counter].path, &s);
                        files[*counter].size = s.st_size;
                        //
                    }
                    *counter = *counter + 1;               
                }
                free(path);
            }
            bpos += current_dir->d_reclen;
        }
    }
    return;
}

DATA_FILE* get_files(char** input, int input_size, int* files_size){
    int to_alloc = 0;
    int i;
    DATA_FILE* ret_files;
    for (i = 0; i < input_size; i++){
        if ( ends_with_txt(input[i])){
            to_alloc++;
        } else {
            if (open(input[i],O_RDONLY | O_DIRECTORY) != 1){
                visit_recursive(input[i],0,NULL,&to_alloc);
            }
        }
    }
    ret_files = (DATA_FILE*) malloc (sizeof(DATA_FILE) * to_alloc);
    *files_size = to_alloc;
    int index = 0;
    for (i = 0; i < input_size; i++){
        if (ends_with_txt(input[i])){
            asprintf(&ret_files[index].path, "%s", input[i]);
            init_zero(&ret_files[index]);
            
            //
            struct stat s;
            stat(ret_files[index].path, &s);
            ret_files[index].size = s.st_size;
            //


            index++;
        } else {
            if (open(input[i], O_RDONLY | O_DIRECTORY) != -1){
                visit_recursive(input[i], WRITE_MODE, ret_files, &index);
            }
        }
    }
    return ret_files;
}



void dealloc_FILES(DATA_FILE* files, int size){
   // printf("Deallocation started..");
    int i;
    for (i = 0; i < size; i++){
        free(files[i].path);
    }
    free(files);
    //printf("DONE!\n");
}


int print_file_short(DATA_FILE* file, bool case_sensitive, bool percentage){
    unsigned long  tot = total_letter_from_file(file);
    
   
    if(percentage){
        printf("%-50s|\n", basename(file->path));
        printf("%-18s|", "       Type");
        printf("%-10s |", "  Quantity  ");
        printf("%-17s|\n", "   Percentage");
        if(case_sensitive){
            printf("Alpha_upper       | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper,fabs((float) ((float)file->data_info.alpha_lower / (float)tot) * 100.0), "%");
            printf("Aplha_over        | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_lower,fabs((float) ((float)file->data_info.alpha_lower / (float)tot) * 100.0), "%");
        } else {
            printf("Alpha             | %-12d|      %-7.2f%s   |\n", file->data_info.alpha_upper + file->data_info.alpha_lower, fabs((float) (((float)(file->data_info.alpha_upper + file->data_info.alpha_lower)) / (float)tot) * 100.0), "%");
        }
        printf("Digit             | %-12d|      %-7.2f%s   |\n", file->data_info.digit, fabs((float) ((float)file->data_info.digit / (float)tot) * 100.0), "%");
        printf("Punct             | %-12d|      %-7.2f%s   |\n", file->data_info.punct, fabs((float) ((float)file->data_info.punct / (float)tot) * 100.0), "%");
        printf("Space             | %-12d|      %-7.2f%s   |\n", file->data_info.space, fabs((float) ((float)file->data_info.space / (float)tot) * 100.0), "%");
        printf("Other             | %-12d|      %-7.2f%s   |\n", file->data_info.other, fabs((float) ((float)file->data_info.other / (float)tot) * 100.0), "%");
    } else {
        printf("%-50s|\n", basename(file->path));
        printf("%-18s|", "       Type");
        printf("%-30s |\n", "  Quantity  ");
        if(case_sensitive){
            printf("Alpha_upper       | %-30d|\n", file->data_info.alpha_upper);
            printf("Aplha_over        | %-30d|\n", file->data_info.alpha_lower);
        } else {
            printf("Alpha             | %-30d|\n", file->data_info.alpha_upper + file->data_info.alpha_lower);
        }
        printf("Digit             | %-30d|\n", file->data_info.digit);
        printf("Punct             | %-30d|\n", file->data_info.punct);
        printf("Space             | %-30d|\n", file->data_info.space);
        printf("Other             | %-30d|\n", file->data_info.other);
    }
    printf("\n\n");
    fflush(stdout);
    return 0;

}
