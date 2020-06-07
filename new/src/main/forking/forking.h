#ifndef FK_FORKING
#define FK_FORKING

/* IMPORTS */

#include "../../../libs/general/general.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* VARIABLES */

extern int fk_main_to_analyzer_pipe[2];
extern int fk_analyzer_to_main_pipe[2];

extern int fk_main_to_reporter_pipe[2];
extern int fk_reporter_to_main_pipe[2];

/* FUNCTIONS */

void fk_init_pipes();
char *fk_get_str_pid();
int fk_fork();
void fk_pipe_redirect_out(int p[2]);
void fk_close(int fd);
void fk_pipe_redirect_in(int p[2]);
void fk_set_nonblock(int fd);
int fk_pipe_read_async(int fd, void* buffer, int amount);

#endif