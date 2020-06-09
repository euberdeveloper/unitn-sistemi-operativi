#include "communication.h"

/* HELPER CONSTANTS */

static const char* _CM_NAMED_PIPE_ID = "/tmp/hope";

/* HELPER FUNCTIONS DECLARATIONS */

void _cm_write_pipe(data_file* cm_data, int cm_data_size);

/* EXPORTED FUNCTIONS */


void cm_schiken(data_file* cm_data, int cm_data_size) {
    _cm_write_pipe(cm_data, cm_data_size);
}

/* HELPER FUNCIONS DEFINITIONS */

void _cm_write_pipe(data_file* cm_data, int cm_data_size) {
    int fd;

    write(fd, &cm_data_size, sizeof(int));

    unsigned long long temp_data_info[6];

    int i, path_length;
    for (i = 0; i < cm_data_size; i++) {
        mkfifo(_CM_NAMED_PIPE_ID, 0666);

        fd = open(_CM_NAMED_PIPE_ID, O_WRONLY);
        if (fd == -1) {
            gn_abort("Error in opening named pipe", 23);
        }

        path_length = (int) strlen(cm_data[i].path);
        write(fd, &path_length, sizeof(int));

        write(fd, cm_data[i].path, path_length * sizeof(char));

        temp_data_info[0] = cm_data[i].data_info.alpha_upper;
        temp_data_info[1] = cm_data[i].data_info.alpha_lower;
        temp_data_info[2] = cm_data[i].data_info.digit;
        temp_data_info[3] = cm_data[i].data_info.punct;
        temp_data_info[4] = cm_data[i].data_info.space;
        temp_data_info[5] = cm_data[i].data_info.other;

        write(fd, temp_data_info, 6 * sizeof(unsigned long long));

        close(fd);
    }
}
