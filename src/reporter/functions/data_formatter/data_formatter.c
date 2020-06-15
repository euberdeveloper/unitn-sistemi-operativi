#include "data_formatter.h"

#define _DF_PATH_HEADER "%-34s |"
#define _DF_DATA_HEADER "%-26s |"
#define _DF_DATA_COL "%-26lli |"
#define _DF_DATA_COL_PERC "%-20lli%6.2f |"
#define _DF_PATH_COL "%-34s |"
#define _DF_SHOWN_PATH_LENGTH 10

/* HELPER FUNCTIONS SIGNATURES */

static void _df_print_path_header(char* str);
static void _df_print_data_header(char* str);
static void _df_print_data_col(const unsigned long long *data);
static void _df_print_data_col_perc(const unsigned long long *data, const unsigned long long *denominator);
static void _df_print_path_col(char* str);
static void _df_newline();
static bool _df_is_path_contained(char** files, int files_size, char* file_to_find);
static char* _df_ellipse_path(char* path, int length);
static void _df_print_header(bool sensitive, bool detailed);
static void _df_get_data_table(unsigned long long data_table[6], char** files, int files_size, data_file* files_data, int files_data_size);
static void _df_get_denominator(unsigned long long *denominator, const unsigned long long data_table[6], bool percentage);
static void _df_print_undetailed_line(bool sensitive, bool percentage, const unsigned long long *denominator, const unsigned long long data_table[6]);
static void _df_print_undetailed_data(bool sensitive, bool percentage, char** files, int files_size, data_file* files_data, int files_data_size);
static void _df_print_detailed_data_file(bool sensitive, bool percentage, const data_file* file);
static void _df_print_detailed_data(bool sensitive, bool percentage, bool total, char** files, int files_size, data_file* files_data, int files_data_size);
static void _df_print_data(bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size, data_file* files_data, int files_data_size);

/* EXPORTED FUNCTIONS */

void df_show_formatted_data(bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size, data_file* files_data, int files_data_size) {
    _df_print_header(sensitive, detailed);
    _df_print_data(sensitive, percentage, detailed, total, files, files_size, files_data, files_data_size);
}

/* HELPER FUNCTIONS DEFINITIONS */

static void _df_print_path_header(char* str) {
    printf(_DF_PATH_HEADER, str);
}
static void _df_print_data_header(char* str) {
    printf(_DF_DATA_HEADER, str);
}
static void _df_print_data_col(const unsigned long long *data) {
    printf(_DF_DATA_COL, *data);
}
static void _df_print_data_col_perc(const unsigned long long *data, const unsigned long long *denominator) {
    printf(_DF_DATA_COL_PERC, *data, ((double) *data / *denominator * 100.0));
}
static void _df_print_path_col(char* str) {
    printf(_DF_PATH_COL, str);
}
static void _df_newline() {
    puts("");
}

static bool _df_is_path_contained(char** files, int files_size, char* file_to_find) {
    bool is_contained = false;

    int i;
    for (i = 0; i < files_size && !is_contained; i++)
    {
        if (strcmp(files[i], file_to_find) == 0)
        {
            is_contained = true;
        }
    }

    return is_contained;
}

static char* _df_ellipse_path(char* path, int length) {
    char* ellipsed;
    int path_len = strlen(path);

    if (path_len < length) {
        ellipsed = strdup(path);
    }
    else {
        char* temp = &path[path_len - (length - 3)];
        asprintf(&ellipsed, "...%s", temp);
    }

    return ellipsed;
}

static void _df_print_header(bool sensitive, bool detailed) {
    if (detailed) {
        _df_print_path_header("PATH");
    }
    if (sensitive){
        _df_print_data_header("UPPERCASE SYMBOLS");
        _df_print_data_header("LOWERCASE SYMBOLS");
    } 
    else {
         _df_print_data_header("ALPHA SYMBOLS");
    }
    _df_print_data_header("DIGIT SYMBOLS");
    _df_print_data_header("PUNCT SYMBOLS");
    _df_print_data_header("SPACE SYMBOLS");
    _df_print_data_header("OTHER SYMBOLS");
    _df_newline();
}

static void _df_get_data_table(unsigned long long data_table[6], char** files, int files_size, data_file* files_data, int files_data_size) {
    int i;

    for (i = 0; i < 6; i++) {
        data_table[i] = 0;
    }

    for (i = 0; i < files_data_size; i++) {
        if (files_size == 0 || _df_is_path_contained(files, files_size, files_data[i].path)) {
            data_table[0] += files_data[i].data_info.alpha_upper;
            data_table[1] += files_data[i].data_info.alpha_lower;
            data_table[2] += files_data[i].data_info.digit;
            data_table[3] += files_data[i].data_info.punct; 
            data_table[4] += files_data[i].data_info.space;
            data_table[5] += files_data[i].data_info.other;
        }
    }
}
static void _df_get_denominator(unsigned long long *denominator, const unsigned long long data_table[6], bool percentage) {
    *denominator = 0;
    
    if (percentage) {
        int i;
        for (i = 0; i < 6; i++) {
            *denominator += data_table[i];
        }   
    }
}

static void _df_print_undetailed_line(bool sensitive, bool percentage, const unsigned long long *denominator, const unsigned long long data_table[6]) {
    if (sensitive) {
        if (percentage) {
            _df_print_data_col_perc(&data_table[0], denominator);
            _df_print_data_col_perc(&data_table[1], denominator);
            _df_print_data_col_perc(&data_table[2], denominator);
            _df_print_data_col_perc(&data_table[3], denominator);
            _df_print_data_col_perc(&data_table[4], denominator);
            _df_print_data_col_perc(&data_table[5], denominator);
        }
        else {
            _df_print_data_col(&data_table[0]);
            _df_print_data_col(&data_table[1]);
            _df_print_data_col(&data_table[2]);
            _df_print_data_col(&data_table[3]);
            _df_print_data_col(&data_table[4]);
            _df_print_data_col(&data_table[5]);
        }
    }
    else {
        unsigned long long total_alpha = data_table[0] + data_table[1];

        if (percentage) {
            _df_print_data_col_perc(&total_alpha, denominator);
            _df_print_data_col_perc(&data_table[2], denominator);
            _df_print_data_col_perc(&data_table[3], denominator);
            _df_print_data_col_perc(&data_table[4], denominator);
            _df_print_data_col_perc(&data_table[5], denominator);
        }
        else {
            _df_print_data_col(&total_alpha);
            _df_print_data_col(&data_table[2]);
            _df_print_data_col(&data_table[3]);
            _df_print_data_col(&data_table[4]);
            _df_print_data_col(&data_table[5]);
        }
    }
    puts("");
}

static void _df_print_undetailed_data(bool sensitive, bool percentage, char** files, int files_size, data_file* files_data, int files_data_size) {
    unsigned long long data_table[6];
    unsigned long long denominator;
    
    _df_get_data_table(data_table, files, files_size, files_data, files_data_size);
    _df_get_denominator(&denominator, data_table, percentage);
    _df_print_undetailed_line(sensitive, percentage, &denominator, data_table);
}

static void _df_print_detailed_data_file(bool sensitive, bool percentage, const data_file* file) {
    char *ellipsed_path = _df_ellipse_path(file->path, _DF_SHOWN_PATH_LENGTH);

    if (file->size == 0) {
        percentage = false;
    }
    
    _df_print_path_col(ellipsed_path);

    if (sensitive) {
        if (percentage) {
            _df_print_data_col_perc(&(file->data_info.alpha_lower), &(file->size));
            _df_print_data_col_perc(&(file->data_info.alpha_upper), &(file->size));
            _df_print_data_col_perc(&(file->data_info.digit), &(file->size));
            _df_print_data_col_perc(&(file->data_info.punct), &(file->size));
            _df_print_data_col_perc(&(file->data_info.space), &(file->size));
            _df_print_data_col_perc(&(file->data_info.other), &(file->size));
        }
        else {
            _df_print_data_col(&(file->data_info.alpha_lower));
            _df_print_data_col(&(file->data_info.alpha_upper));
            _df_print_data_col(&(file->data_info.digit));
            _df_print_data_col(&(file->data_info.punct));
            _df_print_data_col(&(file->data_info.space));
            _df_print_data_col(&(file->data_info.other));
        }
    }
    else {
        unsigned long long total_alpha = file->data_info.alpha_lower + file->data_info.alpha_upper;

        if (percentage) {
            _df_print_data_col_perc(&total_alpha, &(file->size));
            _df_print_data_col_perc(&(file->data_info.digit), &(file->size));
            _df_print_data_col_perc(&(file->data_info.punct), &(file->size));
            _df_print_data_col_perc(&(file->data_info.space), &(file->size));
            _df_print_data_col_perc(&(file->data_info.other), &(file->size));
        }
        else {
            _df_print_data_col(&total_alpha);
            _df_print_data_col(&(file->data_info.digit));
            _df_print_data_col(&(file->data_info.punct));
            _df_print_data_col(&(file->data_info.space));
            _df_print_data_col(&(file->data_info.other));
        }
    }
    puts("");

    free(ellipsed_path);
}

static void _df_print_detailed_data(bool sensitive, bool percentage, bool total, char** files, int files_size, data_file* files_data, int files_data_size) {
    int i;
    for (i = 0; i < files_data_size; i++) {
        if (files_size == 0 || _df_is_path_contained(files, files_size, files_data[i].path)) {
            _df_print_detailed_data_file(sensitive, percentage, &files_data[i]);
        }
    }


    if (total) {
        _df_print_path_col("[TOTAL]");
        _df_print_undetailed_data(sensitive, percentage, files, files_size, files_data, files_data_size);
    }
    
}

static void _df_print_data(bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size, data_file* files_data, int files_data_size) {
    if (detailed) {
        _df_print_detailed_data(sensitive, percentage, total, files, files_size, files_data, files_data_size);
    }
    else {
        _df_print_undetailed_data(sensitive, percentage, files, files_size, files_data, files_data_size);
    }
}