#ifndef DF_DATA_FORMATTER
#define DF_DATA_FORMATTER

/* IMPORTS */

#include "../../../../libs/general/general.h"
#include <string.h>

/* FUNCTIONS */

void df_show_formatted_data(bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size, data_file* files_data, int files_data_size);

#endif