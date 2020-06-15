//
// Created by xeno on 08/06/20.
//

#include "util.h"

// XENO SAMA

int **create_pipes(int n_pipes){
    int i, **pipes_fd = (int**) malloc(sizeof(int *) * n_pipes);
    for(i = 0; i < n_pipes; i++){
        pipes_fd[i] = (int *)malloc(sizeof(int) * 2);
        if(pipe(pipes_fd[i]) < 0){
            fprintf(stderr, "%s", "dio can la pipe s'è rotta");
        }
    }
    return pipes_fd;
}

unsigned long long *new_analyze(char *path, range range){
    unsigned long long *vect = (unsigned long long*) calloc(6, sizeof(unsigned long long));
    if(range.end >= 0  && range.start >= 0){
        int i;
        int fd = open(path, O_RDONLY);
        lseek(fd, range.start, SEEK_SET);
        for(i = range.start; i <= range.end; i++){
            char c;
            read(fd, &c, sizeof(char));
            if (c >= '0' && c <= '9'){
                vect[2] += 1;
            } else if (c >= 'a' && c <= 'z'){
                vect[1] += 1;
            } else if (c >= 'A' && c <= 'Z'){
                vect[0] += 1;
            } else if (c == ' '){
                vect[4] += 1;
            } else if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~')){
                vect[3] += 1;
            } else {
                vect[5] +=1;
            }
        }
    }
    return vect;
}

data_info vect_to_data_info(unsigned long long *vect){
    int i = 0;
    data_info data;
    //printf("i : %d | data : %llu\n", i, vect[i]);
    data.alpha_upper = (int)vect[i++];
    //printf("i : %d | data : %llu\n", i, vect[i]);
    data.alpha_lower = (int)vect[i++];
    //printf("i : %d | data : %llu\n", i, vect[i]);
    data.digit = (int)vect[i++];
    //printf("i : %d | data : %llu\n", i, vect[i]);
    data.punct = (int)vect[i++];
    //printf("i : %d | data : %llu\n", i, vect[i]);
    data.space = (int)vect[i++];
    //printf("i : %d | data : %llu\n\n", i, vect[i]);
    data.other = (int)vect[i];
    return data;
}

void show_vect(unsigned long long *vect){
    int i = 0;
    printf("data%d: %llu\n",i, vect[i]); i++;
    printf("data%d: %llu\n",i, vect[i]); i++;
    printf("data%d: %llu\n",i, vect[i]); i++;
    printf("data%d: %llu\n",i, vect[i]); i++;
    printf("data%d: %llu\n",i, vect[i]); i++;
    printf("data%d: %llu\n",i, vect[i]);
}



// SEBGOD

bool ends_with_txt(char* str){
    return (strcmp(&str[strlen(str) - 4], TXT) == 0);
}

void init_zero(data_file * file){
    file->data_info.alpha_lower = 0;
    file->data_info.alpha_upper = 0;
    file->data_info.digit = 0;
    file->data_info.other = 0;
    file->data_info.punct = 0;
    file->data_info.space = 0;
}

int is_duplicates(char **inputs, int input_size, char *str2, int str2_index, int *appereance)
{
    int i;
    bool found = false;
    for (i = 0; i < input_size; i++)
    {
        if (i != str2_index)
        {
            if (strstr(inputs[i], str2) != NULL)
            { //search str2 within inputs[i]
                appereance[i] = 1;
                found = true;
                // printf("found at %d\n", i);
            }
        }
    }

    return found;
}

char **parse_input_no_dup(char **input, int input_size, int *new_input_size)
{
    int *appereance;
    appereance = (int *)malloc(sizeof(int) * input_size);
    int i, j;
    for (i = 0; i < input_size; i++)
    {
        appereance[i] = 0;
    }
    for (i = 0; i < input_size; i++)
    {
        if (appereance[i] == 0)
        {
            is_duplicates(input, input_size, input[i], i, appereance);
        }
    }
    *new_input_size = 0;
    for (j = 0; j < input_size; j++)
    {
        if (appereance[j] == 0)
        {
            *new_input_size += 1;
        }
    }
    char **ret;
    ret = (char **)malloc(sizeof(char *) * (*new_input_size));
    int index = 0;
    for (j = 0; j < input_size; j++)
    {
        if (appereance[j] == 0)
        {
            asprintf(&ret[index], "%s", input[j]);
            index++;
        }
    }
    for (i = 0; i < input_size; i++)
    {
        //free(input[i]);
    }
    // free(input);
    //printf("new _input_size = %d\n", *new_input_size);
    free(appereance);
    return ret;
}

bool is_readable(char *path)
{
    bool res;
    int fd = open(path, O_DIRECTORY);
    if (fd != -1)
    {
        close(fd);
        return false;
    }
    struct stat s;
    stat(path, &s);
    if (s.st_mode & R_OK)
    {
        res = true;
    }
    else
    {
        res = false;
    }
    return res;
}

void visit_recursive(char *name, int mode, data_file *files, int *counter)
{
    linux_dirent *current_dir;
    int nread;
    int bpos;
    int fd;
    int fd_2;
    char buf[BUFF_SIZE];
    bool is_dir = true;
    fd = open(name, O_RDONLY | O_DIRECTORY);
    if (fd == -1)
    {
        printf("'%s' is not a directory\n", name);
        return;
    }
    while (is_dir)
    {

        nread = syscall(SYS_getdents, fd, buf, BUFF_SIZE);
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
                    visit_recursive(path, mode, files, counter);
                }
                if (is_readable(path))
                {

                    if (mode == WRITE_MODE)
                    {
                        //printf("storing --> %s\n", path);
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

void old_visit_recursive(char *name,  int mode, data_file * files, int* counter){
    //printf("Recursive\n");
    linux_dirent *current_dir;
    int nread;
    int bpos;
    int fd;
    int fd_2;
    char buf[BUFF_SIZE];
    bool is_dir = true;
    fd = open(name, O_RDONLY | O_DIRECTORY);
    if (fd == -1){
        //printf("'%s' is not a directory\n", name);
        return;
    }
    while (is_dir){
        nread = syscall(SYS_getdents, fd, buf, BUFF_SIZE);
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

files_array get_files(char **input, int input_size, bool duplicate)
{
    int to_alloc = 0;
    int i;
    int new_input_size;
    char **new_input;
    files_array res;
    ///
    if (!duplicate)
    {
        new_input_size = input_size;
        new_input = input;
    }
    else
    {
        new_input_size = input_size;
        new_input = parse_input_no_dup(input, input_size, &new_input_size);
    }

    for (i = 0; i < new_input_size; i++)
    {
        //printf(" new input : %d--> %s\n", i,new_input[i]);
    }

    ///
    data_file *ret_files;
    for (i = 0; i < new_input_size; i++)
    {

        if (is_readable(new_input[i]))
        {
            to_alloc++;
        }
        else
        {

            if (open(new_input[i], O_RDONLY | O_DIRECTORY) != 1)
            {
                visit_recursive(new_input[i], 0, NULL, &to_alloc);
            }
        }


    }
    //printf("to alloc = %d\n", to_alloc);
    ret_files = (data_file *)malloc(sizeof(data_file) * to_alloc);
    int index = 0;
    for (i = 0; i < new_input_size; i++)
    {

        if (is_readable(new_input[i]))
        {
            //printf("is readable ---> %s\n", new_input[i]);
            asprintf(&ret_files[index].path, "%s", new_input[i]);
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
            if (open(new_input[i], O_RDONLY | O_DIRECTORY) != -1)
            {
                visit_recursive(new_input[i], WRITE_MODE, ret_files, &index);
            }
        }
    }
    res.size = index;
    res.files = ret_files;
    return res;
}

files_array old_get_files(char** input, int input_size){
    int to_alloc = 0;
    int i;
    files_array res;
    data_file* ret_files;
    for (i = 0; i < input_size; i++){
        if ( ends_with_txt(input[i])){
            to_alloc++;
        } else {
            if (open(input[i],O_RDONLY | O_DIRECTORY) != 1){
                visit_recursive(input[i],0,NULL,&to_alloc);
            }
        }
    }
    ret_files = (data_file*) malloc (sizeof(data_file) * to_alloc);
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
    res.files = ret_files;
    res.size = to_alloc;
    return res;
}

void analyze(data_file* file_to_analize ,range range){
    int i;
    int fd  = open(file_to_analize->path, O_RDONLY);
    lseek(fd, range.start, SEEK_SET);
    for (i = range.start; i <= range.end; i++){
        char c;
        read(fd, &c, sizeof(char));
        if (c >= '0' && c <= '9'){
            file_to_analize->data_info.digit += 1;
        } else if (c >= 'a' && c <= 'z'){
            file_to_analize->data_info.alpha_lower += 1;
        } else if (c >= 'A' && c <= 'Z'){
            file_to_analize->data_info.alpha_upper += 1;
        } else if (c == ' '){
            file_to_analize->data_info.space += 1;
        } else if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~')){
            file_to_analize->data_info.punct += 1;
        } else {
            file_to_analize->data_info.other +=1;
        }
    }
    close(fd);
}


range* get_ranges_from_size(char* path, int number_of_q) {
    range *res = (range*) malloc(sizeof(range) * number_of_q);
    int i;
    if(strcmp(path, EOT) != 0) {
        unsigned long long size;
        struct stat s;
        stat(path, &s);
        size = s.st_size;
        //printf("Size : %llu\n", size);
        if(number_of_q >= size){
            for(i = 0; i < size; i++){
                res[i].start = i;
                res[i].end = i;
            }for(; i < number_of_q; i++){
                res[i].start = -1;
                res[i].end = -1;
            }
        }else {
            int d = size / number_of_q - 1 ;

            for (i = 0; i < number_of_q; i++) {
                if(i == number_of_q - 1){
                    res[i].start = (d * i) + i*1;
                    res[i].end = size - 1;
                }else{
                    if(i == 0)
                        res[i].start = d * i;
                    else
                        res[i].start = (d * i) + i*1;

                    res[i].end = res[i].start + d;
                }
            }
        }
    }else{
        for (i = 0; i < number_of_q; i++){
            res[i].start = -1;
            res[i].end = -1;
        }
    }
    return res;
}

/*range* get_ranges_from_size(char* path, int number_of_q){
    range* ret;
    ret = (range*) malloc (sizeof(range) * number_of_q);
    int i;
    if(strcmp(path, EOT) != 0){
        unsigned long long size;
        struct stat s;
        stat(path, &s);
        size = s.st_size;
        if(size >= number_of_q){
            int level = 1;
            int step = size / number_of_q;
            for (i = 0; i < number_of_q; i++){
                ret[i].start = (level - 1) * step;
                if (level == number_of_q){
                    ret[i].end = size - 1;
                } else {
                    ret[i].end = level*step - 1;
                }
                level++;
            }
        }else{
            for (i = 0; i < size; i++){
                ret[i].start = i;
                ret[i].end = i;
            }for(; i < number_of_q; i++){
                ret[i].start = -1;
                ret[i].end = -1;
            }
        }
    }
    else{
        for (i = 0; i < number_of_q; i++){
            ret[i].start = -1;
            ret[i].end = -1;
        }
    }

    return ret;
}*/

p_input *get_P_input(data_file *files, int files_size, int number_of_P)
{
    if(number_of_P == 0){
        //printf("rotto l'input\n");
        return NULL;
    }
    if (number_of_P == 1)
    {
        //printf("case p = 1\n");
        int i;
        p_input *ret_ps = (p_input *)malloc(sizeof(p_input) * number_of_P );
        ret_ps[0].paths = (char **)malloc(sizeof(char *) * (files_size + 1));
        for (i = 0; i < files_size; i++)
        {
            ret_ps[0].paths[i] = strdup(files[i].path);
            ret_ps[0].path_size = 1;
        }
        ret_ps[0].paths[files_size] = strdup("EOT");
        ret_ps[0].path_size = files_size + 1;
        return ret_ps;
    }
    else
    {
        if (files_size > number_of_P)
        {
            //printf("case files_size > number_of_p\n");
            int divide = files_size / number_of_P;
            //printf("divide = %d\n", divide);
            int scarto = files_size % number_of_P;
            //printf("scarto = %d\n", scarto);
            int data_file_to_alloc;
            int i, j;
            int next_file_index = 0;
            int p_index = 0;
            p_input *ret_Ps = (p_input *)malloc(sizeof(p_input) * number_of_P);
            for (i = 1; i <= number_of_P; i++)
            {
                if (scarto != 0)
                {
                    data_file_to_alloc = divide + 1;
                    scarto--;
                }
                else
                {
                    data_file_to_alloc = divide;
                }

                //ret_Ps[p_index].files_indexes = (data_file*) malloc (sizeof(data_file) * data_file_to_alloc);

                //printf("data file to alloc = %d\n", data_file_to_alloc);
                //ret_Ps[p_index].files_size = data_file_to_alloc;
                //ret_Ps[p_index].files_indexes = files + next_file_index;

                ret_Ps[p_index].path_size = data_file_to_alloc + 1;
                ret_Ps[p_index].paths = (char **)malloc(sizeof(char *) * (data_file_to_alloc + 1));
                //ret_Ps[p_index].sizes = (unsigned long long *)malloc(sizeof(unsigned long long) * data_file_to_alloc);
                for (j = 0; j < data_file_to_alloc; j++)
                {
                    asprintf(&ret_Ps[p_index].paths[j], "%s", files[next_file_index].path);
                    next_file_index++;
                    //ret_Ps[p_index].sizes[j] = files[j + next_file_index].size;
                }

                //ret_Ps[p_index].paths[data_file_to_alloc] = strdup("EOT");
                asprintf(&ret_Ps[p_index].paths[data_file_to_alloc], "%s", "EOT");
                //next_file_index += data_file_to_alloc+1;
                p_index++;

            }
            return ret_Ps;
        }
        else
        {
            //printf("case 3\n");
            p_input *ret_ps = (p_input *)malloc(sizeof(p_input) * number_of_P);
            int i;
            /*
            for (i = 0; i < files_size; i++){
                printf("file %d --> %s\n", i, files[i].path);
            }*/

            for (i = 0; i < files_size; i++)
            {
                ret_ps[i].paths = (char **)malloc(sizeof(char *) * 2);
                //ret_ps[i].paths[0] = strdup(files[i].path);
                asprintf(&ret_ps[i].paths[0], "%s", files[i].path);
                asprintf(&ret_ps[i].paths[1], "%s", EOT);
                ret_ps[i].path_size = 2;
            }

            for (i = files_size; i < number_of_P; i++)
            {
                ret_ps[i].paths = (char **)malloc(sizeof(char *) * 1);
                ret_ps[i].paths[0] = strdup("EOT");
                ret_ps[i].path_size = 1;
            }

            /*for(i = 0; i < number_of_P; i++){
                printf(" P(%d) --> %s\n files sizes = %d\n\n", i, ret_ps[i].paths[0], ret_ps[i].path_size);
            }*/
            return ret_ps;
        }
    }
};