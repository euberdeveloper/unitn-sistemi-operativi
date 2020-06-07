#include "R_functions_final.h"
#include "../../Queue/queue.h"
#include <math.h>

#define LINE "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"

unsigned long long int total_letter_from_file(DATA_FILE *file)
{
    return (file->data_info.alpha_lower + file->data_info.alpha_upper + file->data_info.digit + file->data_info.punct + file->data_info.space + file->data_info.other);
}

bool ends_with_txt(char *str)
{
    return (strcmp(&str[strlen(str) - 4], TXT) == 0);
}

void init_zero(DATA_FILE *file)
{
    file->data_info.alpha_lower = 0;
    file->data_info.alpha_upper = 0;
    file->data_info.digit = 0;
    file->data_info.other = 0;
    file->data_info.punct = 0;
    file->data_info.space = 0;
}

bool is_in_datafile(DATA_FILE *files, int files_size, char *element)
{
    int i;
    for (i = 0; i < files_size; i++)
    {
        if (strcmp(files[i].path, element) == 0)
        {
            return true;
        }
    }
    return false;
}
/*
//FIX DUPLICATE
void visit_recursive(char *name, int mode, DATA_FILE *files, int *counter, int *true_counter, bool duplicate)
{
    //printf("Recursive\n");
    linux_dirent *current_dir;
    int nread;
    int bpos;
    int fd;
    int fd_2;
    char buf[BUF_SIZE];
    bool is_dir = true;
    fd = open(name, O_RDONLY | O_DIRECTORY);
    if (fd == -1)
    {
        printf("'%s' is not a directory\n", name);
        return;
    }
    while (is_dir)
    {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == 0)
        {
            is_dir = false;
        }
        for (bpos = 0; bpos < nread;)
        {
            current_dir = (linux_dirent *)(buf + bpos);
            if (strcmp(current_dir->d_name, ".") != 0 && strcmp(current_dir->d_name, "..") != 0)
            {
                char *path;
                asprintf(&path, "%s/%s", name, current_dir->d_name);
                fd_2 = open(path, O_RDONLY | O_DIRECTORY);
                if (fd_2 != -1)
                {
                    close(fd_2);
                    visit_recursive(path, mode, files, counter, true_counter, duplicate);
                }
                if (ends_with_txt(path))
                {
                    if (mode == WRITE_MODE && !is_in_datafile(files, *true_counter, path))
                    {
                        asprintf(&files[*counter].path, "%s", path);
                        init_zero(&files[*counter]);
                        //
                        struct stat s;
                        stat(files[*counter].path, &s);
                        files[*counter].size = s.st_size;
                        //
                        *true_counter = *true_counter + 1;
                    }
                    *counter = *counter + 1;
                }
                free(path);
            }
            bpos += current_dir->d_reclen;
        }
    }
    close(fd);
    return;
}

//ADD mod_t? from stat()
DATA_FILE *get_files(char **input, int input_size, int *files_size, bool duplicate)
{
    int to_alloc = 0;
    int true_counter = 0;
    int i;
    DATA_FILE *ret_files;
    for (i = 0; i < input_size; i++)
    {
        if (ends_with_txt(input[i]))
        {
            to_alloc++;
        }
        else
        {
            if (open(input[i], O_RDONLY | O_DIRECTORY) != 1)
            {
                visit_recursive(input[i], 0, NULL, &to_alloc, &true_counter, duplicate);
            }
        }
    }
    printf("true counter = %d\n, to alloc = %d\n", true_counter, to_alloc);
    //  ret_files = (DATA_FILE*) malloc (sizeof(DATA_FILE) * (to_alloc + 1));
    ret_files = (DATA_FILE *)malloc(sizeof(DATA_FILE) * to_alloc);
    true_counter = 0;
    int index = 0;
    for (i = 0; i < input_size; i++)
    {
        if (duplicate)
        {
            if (ends_with_txt(input[i]) && !is_in_datafile(ret_files, index, input[i]))
            {
                asprintf(&ret_files[index].path, "%s", input[i]);
                init_zero(&ret_files[index]);
                //
                struct stat s;
                stat(ret_files[index].path, &s);
                ret_files[index].size = s.st_size;
                //
                index++;
            }
            else
            {
                if (open(input[i], O_RDONLY | O_DIRECTORY) != -1)
                {
                    visit_recursive(input[i], WRITE_MODE, ret_files, &index, &true_counter, duplicate);
                }
            }
        } else {
            if (ends_with_txt(input[i]))
            {
                asprintf(&ret_files[index].path, "%s", input[i]);
                init_zero(&ret_files[index]);
                //
                struct stat s;
                stat(ret_files[index].path, &s);
                ret_files[index].size = s.st_size;
                //
                index++;
            }
            else
            {
                if (open(input[i], O_RDONLY | O_DIRECTORY) != -1)
                {
                    visit_recursive(input[i], WRITE_MODE, ret_files, &index, &true_counter, duplicate);
                }
            }
        }
    }
    
    if (true_counter < to_alloc)
    {   
        for (i = true_counter - 1; i < (to_alloc - true_counter); i++){
            free(ret_files[i].path);
            free(&ret_files[i]);
        }
    }
    *files_size = true_counter;

    // ret_files[to_alloc + 1].path = NULL;
    return ret_files;
}


*/
void visit_recursive(char *name,  int mode, DATA_FILE* files, int* counter){
    //printf("Recursive\n");
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
    close(fd);
    return;
}

int is_duplicates(char** inputs, int input_size, char* str2, int str2_index, int* appereance){
    int i;
    bool found = false;
    for (i = 0; i < input_size; i++){
        if (i != str2_index){
            if(strstr(inputs[i],str2) != NULL){//search str2 within inputs[i]
               appereance[i] = 1;
               found = true;
             // printf("found at %d\n", i);
            }
        }   
    }
    
    return found; 
}

char** parse_input_no_dup(char** input, int input_size, int* new_input_size){
    int* appereance;
    appereance = (int*) malloc (sizeof(int) * input_size );
    int i,j;
    for(i = 0; i < input_size; i++){
        appereance[i] = 0;
    }
    for(i = 0; i < input_size; i++){
        if (appereance[i] == 0){
            is_duplicates(input, input_size, input[i],i , appereance);
        }
    }
    *new_input_size = 0;
    for (j = 0 ;j < input_size; j++){
        if (appereance[j] == 0){
            *new_input_size += 1;
        }
    }
    char** ret;
    ret = (char**) malloc (sizeof(char*) * (*new_input_size));
    int index = 0;
    for (j = 0; j < input_size; j++){
        if(appereance[j] == 0){
            asprintf(&ret[index], "%s", input[j]);
            index++;
        }
    }
    for(i = 0; i < input_size; i++){
        //free(input[i]);
    }
   // free(input);
    printf("new _input_size = %d\n", *new_input_size);
    free(appereance);
    return ret;
}



DATA_FILE* get_files(char** input, int input_size, int* files_size, bool duplicate){
    int to_alloc = 0;
    int i;
    int new_input_size;
    char** new_input;
    ///
    if(!duplicate){    
        new_input_size = input_size;
        new_input = input;//parse_input_no_dup(input, input_size, &new_input_size);
    } else {
        new_input_size = input_size;
        new_input = parse_input_no_dup(input, input_size, &new_input_size);
    }

    ///
    DATA_FILE* ret_files;
    for (i = 0; i < new_input_size; i++){
        if ( ends_with_txt(new_input[i])){
            to_alloc++;
        } else {
            if (open(input[i],O_RDONLY | O_DIRECTORY) != 1){
                visit_recursive(new_input[i],0,NULL,&to_alloc);
            }
        }
    }
    ret_files = (DATA_FILE*) malloc (sizeof(DATA_FILE) * to_alloc);
    *files_size = to_alloc;
    int index = 0;
    for (i = 0; i < new_input_size; i++){
        if (ends_with_txt(new_input[i])){
            asprintf(&ret_files[index].path, "%s", new_input[i]);
            init_zero(&ret_files[index]);
            
            //
            struct stat s;
            stat(ret_files[index].path, &s);
            ret_files[index].size = s.st_size;
            //


            index++;
        } else {
            if (open(new_input[i], O_RDONLY | O_DIRECTORY) != -1){
                visit_recursive(new_input[i], WRITE_MODE, ret_files, &index);
            }
        }
    }
    //dealloc new_input toADD
    return ret_files;
}



void visit_iterative(char *name, int mode, DATA_FILE *files, int *counter)
{
    Queue Q;
    //printf("Iterative\n");
    init(&Q, 10000); //100 rappresent the number of folders we can handle
    push(&Q, name);
    while (!is_empty(&Q))
    {
        linux_dirent *current_dir;
        int nread;
        int bpos;
        int fd;
        int fd_2;
        char buf[1024 * 1024];
        asprintf(&name, "%s", front(&Q));
        pop(&Q);
        fd = open(name, O_RDONLY | O_DIRECTORY);
        nread = syscall(SYS_getdents, fd, buf, 1024 * 1024);
        if (nread != 0)
        {
            for (bpos = 0; bpos < nread;)
            {
                current_dir = (linux_dirent *)(buf + bpos);
                if (strcmp(current_dir->d_name, ".") != 0 && strcmp(current_dir->d_name, "..") != 0)
                {
                    char *path;
                    asprintf(&path, "%s/%s", name, current_dir->d_name);
                    fd_2 = open(path, O_RDONLY | O_DIRECTORY);
                    if (fd_2 != -1)
                    {
                        close(fd_2);
                        push(&Q, path);
                        //printf("size = %d\n", Q.size);
                    }
                    else
                    {
                        if (ends_with_txt(path))
                        {
                            if (mode == WRITE_MODE)
                            {
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
                    }
                    free(path);
                }
                bpos += current_dir->d_reclen;
            }
        }
        close(fd);
        free(name);
    }
    de_init(&Q);
    return;
}

void dealloc_FILES(DATA_FILE *files, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(files[i].path);
    }
    free(files);
}

char *first_ten(char *str)
{
    char *ret;
    if (strlen(str) < 10)
    {
        ret = (char *)malloc(sizeof(char) * strlen(str));
        strcpy(ret, str);
    }
    else
    {
        ret = (char *)malloc(sizeof(char) * 11);
        int i;
        for (i = 0; i < 10; i++)
        {
            ret[i] = str[i];
        }
        ret[10] = '\0';
    }
    return ret;
}

int print_file_short(DATA_FILE *file, bool case_sensitive, bool percentage)
{

    if (file->size == 0)
    {
        percentage = false;
    }

    char *start = first_ten(file->path);
    printf("%s ... %-35s|", start, basename(file->path));
    free(start);
    if (case_sensitive)
    {
        if (!percentage)
        {
            printf("%-26lli |", file->data_info.alpha_upper);
            printf("%-26lli |", file->data_info.alpha_lower);
        }
        else
        {
            printf("%-20lli%6.2f |", file->data_info.alpha_upper, ((double)file->data_info.alpha_upper / file->size * 100.0));
            printf("%-20lli%6.2f |", file->data_info.alpha_lower, ((double)file->data_info.alpha_lower / file->size * 100.0));
        }
    }
    else
    {
        if (percentage)
        {
            printf("%-20lli%6.2f |", file->data_info.alpha_lower + file->data_info.alpha_upper, ((double)(file->data_info.alpha_lower + file->data_info.alpha_upper) / file->size * 100.0));
        }
        else
        {
            printf("%-26lli |", file->data_info.alpha_lower + file->data_info.alpha_upper);
        }
    }

    if (percentage)
    {
        printf("%-20lli%6.2f |", file->data_info.digit, ((double)file->data_info.digit / file->size * 100.0));
        printf("%-20lli%6.2f |", file->data_info.punct, ((double)file->data_info.punct / file->size * 100.0));
        printf("%-20lli%6.2f |", file->data_info.space, ((double)file->data_info.space / file->size * 100.0));
        printf("%-20lli%6.2f |\n", file->data_info.other, ((double)file->data_info.other / file->size * 100.0));
    }
    else
    {
        printf("%-26lli |", file->data_info.digit);
        printf("%-26lli |", file->data_info.punct);
        printf("%-26lli |", file->data_info.space);
        printf("%-26lli |\n", file->data_info.other);
    }

    fflush(stdout);

    return 0;
}

bool is_in(char **input, int input_size, char *to_find)
{
    int i;
    for (i = 0; i < input_size; i++)
    {
        if (strcmp(input[i], to_find) == 0)
        {
            return true;
        }
    }
    return false;
}

void print_files_one_line(DATA_FILE *files, int files_size, bool sensitive, bool percentage, bool detailed, char **input, int input_size)
{
    int i, j;
    unsigned long long n[6];
    if (input == NULL)
    {
        for (i = 0; i < files_size; i++)
        {
            n[0] += files[i].data_info.alpha_upper;
            n[1] += files[i].data_info.alpha_lower;
            n[2] += files[i].data_info.digit;
            n[3] += files[i].data_info.punct;
            n[4] += files[i].data_info.space;
            n[5] += files[i].data_info.other;
        }
    }
    else
    {
        for (i = 0; i < files_size; i++)
        {
            if (is_in(input, input_size, files[i].path))
            {
                n[0] += files[i].data_info.alpha_upper;
                n[1] += files[i].data_info.alpha_lower;
                n[2] += files[i].data_info.digit;
                n[3] += files[i].data_info.punct;
                n[4] += files[i].data_info.space;
                n[5] += files[i].data_info.other;
            }
        }
    }
    unsigned long long den = 0;
    if (percentage)
    {
        for (i = 0; i < 6; i++)
        {
            den += n[i];
        }
    }

    if (sensitive)
    {
        if (!percentage)
        {
            printf("%-26lli |", n[0]);
            printf("%-26lli |", n[1]);
        }
        else
        {
            printf("%-20lli%6.2f |", n[0], ((double)n[0] / den * 100.0));
            printf("%-20lli%6.2f |", n[1], ((double)n[1] / den * 100.0));
        }
    }
    else
    {
        if (percentage)
        {
            printf("%-20lli%6.2f |", n[0] + n[1], ((double)(n[0] + n[1]) / den * 100.0));
        }
        else
        {
            printf("%-26lli |", n[0] + n[1]);
        }
    }

    if (percentage)
    {
        printf("%-20lli%6.2f |", n[2], ((double)n[2] / den * 100.0));
        printf("%-20lli%6.2f |", n[3], ((double)n[3] / den * 100.0));
        printf("%-20lli%6.2f |", n[4], ((double)n[4] / den * 100.0));
        printf("%-20lli%6.2f |\n", n[5], ((double)n[5] / den * 100.0));
    }
    else
    {
        printf("%-26lli |", n[2]);
        printf("%-26lli |", n[3]);
        printf("%-26lli |", n[4]);
        printf("%-26lli |\n", n[5]);
    }

    fflush(stdout);
}

int show(DATA_FILE *files, int files_size, bool sensitive, bool percentage, bool detailed, char **input, int input_size)
{

    printf(LINE);
    if (detailed)
    {   
        printf("%-49s |", "Basename");
        printf("%-26s |", "alpha_upper");
        printf("%-26s |", "alpha_lower");
        printf("%-26s |", "digit");
        printf("%-26s |", "punct");
        printf("%-26s |", "space");
        printf("%-26s |\n", "other");
        printf(LINE);
        fflush(stdout);
        int i;
        for (i = 0; i < files_size; i++)
        {
            if (input != NULL)
            {
                if (is_in(input, input_size, files[i].path))
                {
                    print_file_short(&files[i], sensitive, percentage);
                    printf(LINE);
                }
            }
            else
            {
                print_file_short(&files[i], sensitive, percentage);
                printf(LINE);
            }
        }
    }
    else
    {
        printf("%-26s |", "alpha_upper");
        printf("%-26s |", "alpha_lower");
        printf("%-26s |", "digit");
        printf("%-26s |", "punct");
        printf("%-26s |", "space");
        printf("%-26s |\n", "other");
        print_files_one_line(files, files_size, sensitive, percentage, detailed, input, input_size);
    }
    fflush(stdout);
    return 0;
}

