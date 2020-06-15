#ifndef FK_FORKING
#define FK_FORKING

/* IMPORTS */

#include "../general/general.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/* DEFINES */

#define READ_END 0
#define WRITE_END 1
#define PARENT_TO_CHILD 0
#define CHILD_TO_PARENT 1

/* FUNCTIONS */

void fk_pipe(int p[2]);
void fk_init_pipes(int p[2][2]);
char *fk_get_str_pid();
int fk_fork();
void fk_pipe_redirect_out(int p[2]);
void fk_close(int fd);
void fk_pipe_redirect_in(int p[2]);
void fk_set_nonblock(int fd);
int fk_pipe_read_async(int fd, void* buffer, int amount);

#endif