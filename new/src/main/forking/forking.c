#include "forking.h"

/* HELPER FUNCTIONS DECLARATIONS */

static void _fk_pipe(int p[2]);

/* EXPORTED VARIABLES */

int fk_main_to_analyzer_pipe[2];
int fk_analyzer_to_main_pipe[2];

int fk_main_to_reporter_pipe[2];
int fk_reporter_to_main_pipe[2];

/* EXPORTED FUNCTIONS */

void fk_init_pipes() {
    _fk_pipe(fk_main_to_analyzer_pipe);
    _fk_pipe(fk_analyzer_to_main_pipe);

    _fk_pipe(fk_main_to_reporter_pipe);
    _fk_pipe(fk_reporter_to_main_pipe);
}

char *fk_get_str_pid() {
    int int_main_pid = getpid();
    char *main_pid;
    asprintf(&main_pid, "%d", int_main_pid);
    return main_pid;
}

int fk_fork() {
    int pid = fork();

    if (pid == -1) {
        gn_abort("Error in forking", ERROR_FORK);
    }
	
    return pid;
}

void fk_close(int fd) {
    if (close(fd) == -1) {
        gn_abort("Error in closing file descriptor", ERROR_DESCRIPTOR_CLOSE);
    }
}

void fk_pipe_redirect_out(int p[2]) {
    dup2(p[WRITE_END], STDOUT_FILENO);
    fk_close(p[READ_END]);
    fk_close(p[WRITE_END]);
}
void fk_pipe_redirect_in(int p[2]) {
    dup2(p[READ_END], STDIN_FILENO);
    fk_close(p[READ_END]);
    fk_close(p[WRITE_END]);
}

void fk_set_nonblock(int fd) {
    if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
        gn_abort("Error in setting a pipe nonblock", ERROR_FCNTL);
    }
}

int fk_pipe_read_async(int fd, void* buffer, int amount) {
    int result = read(fd, buffer, amount);

    if (result == -1 && errno == EAGAIN) {
        //gn_abort("Error in reading pipe", ERROR_PIPE_READ);
    }

    return result;
}

/* HELPER FUNCTIONS DEFINITIONS */

static void _fk_pipe(int p[2]) {
    if (pipe(p) == -1) {
        gn_abort("Error in pipe initialization", ERROR_PIPE_INIT);
    }
}