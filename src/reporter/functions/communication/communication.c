#include "communication.h"

/* HELPER CONSTANTS */

static const char* _CM_NAMED_PIPE_ID = "/tmp/hope";

/* EXPORTED VARIABLES */

data_file *cm_data = NULL;
int cm_data_size = 0;

data_file cm_sleeve_ace[10];

/* HELPER FUNCIONS DECLARATIONS */

void _cm_read_pipe(int fd);

/* EXPORTED FUNCTIONS */

void cm_init_sleeve_ace() {
    int i;
    for (i = 0; i < 10; i++) {
        asprintf(&cm_sleeve_ace[i].path, "/sist/op/%d.pug", i);
        cm_sleeve_ace[i].data_info.alpha_upper = i + 23;
        cm_sleeve_ace[i].data_info.alpha_lower = i + 23;
        cm_sleeve_ace[i].data_info.digit = i + 23;
        cm_sleeve_ace[i].data_info.punct = i + 23;
        cm_sleeve_ace[i].data_info.space = i + 23;
        cm_sleeve_ace[i].data_info.other = i + 23;
    }
}

void cm_fetch() {
    mkfifo(_CM_NAMED_PIPE_ID, 0666);

    int fd = open(_CM_NAMED_PIPE_ID, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        gn_abort("Error in opening named pipe", 23);
    }

    _cm_read_pipe(fd);

    close(fd);
}

/* HELPER FUNCIONS DEFINITIONS */

void _cm_read_pipe(int fd) {
    int outcome = read(fd, &cm_data_size, sizeof(int));

    if (outcome == -1 && errno != EAGAIN) {
        gn_abort("Error in reading named pipe", 25);
    }
    else {
        cm_data = (data_file*) malloc(cm_data_size * sizeof(data_file));

        unsigned long long temp_data_info[6];

        int i, path_length;
        for (i = 0; i < cm_data_size; i++) {
            read(fd, &path_length, sizeof(int));

            cm_data[i].path = (char*) malloc((path_length + 1) * sizeof(char));
            read(fd, cm_data[i].path , path_length * sizeof(char));
            cm_data[i].path[path_length] = '\0';

            read(fd, temp_data_info , 6 * sizeof(unsigned long long));

            cm_data[i].data_info.alpha_upper = temp_data_info[0];
            cm_data[i].data_info.alpha_lower = temp_data_info[1];
            cm_data[i].data_info.digit = temp_data_info[2];
            cm_data[i].data_info.punct = temp_data_info[3];
            cm_data[i].data_info.space = temp_data_info[4];
            cm_data[i].data_info.other = temp_data_info[5];
        }        
    }
}
