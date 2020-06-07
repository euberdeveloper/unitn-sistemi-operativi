#include "functions.h"

/* HELPER VARIABLES AND STRUCTURES */

typedef struct {
    int fd;
    bool* wait_output_written;
} _thread_handler_arguments_t;

static pthread_t _analyzer_output_thread;
static pthread_t _reporter_output_thread;

static bool _wait_output_written_analyzer = false;
static bool _wait_output_written_reporter = false;

/* HELPER FUNCTIONS DECLARATIONS */

static void _forward_and_wait(int pipe[], bool* wait_output_written);
static void _create_thread(pthread_t* thread, void *(*thread_handler) (void *), void* arguments);
static void *_thread_handler_analizer(void* args);
static void *_thread_handler_reporter(void* args);

/* EXPORTED FUNCTIONS */

SH_STATE arguments(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    sig_init_signals();
}

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}

SH_STATE status() {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}
SH_STATE stop() {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    return SH_CONTINUE;
}

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    _forward_and_wait(fk_main_to_reporter_pipe, &_wait_output_written_reporter);
    return SH_CONTINUE;
}

SH_STATE quit() {
    _forward_and_wait(fk_main_to_analyzer_pipe, &_wait_output_written_analyzer);
    _forward_and_wait(fk_main_to_reporter_pipe, &_wait_output_written_reporter);
    return SH_EXIT;
}

void init_analyzer_output_thread() {
    _thread_handler_arguments_t *arguments = (_thread_handler_arguments_t*) malloc(sizeof(_thread_handler_arguments_t));
    arguments->fd = fk_analyzer_to_main_pipe[READ_END];
    arguments->wait_output_written = &_wait_output_written_analyzer;

    _create_thread(&_analyzer_output_thread, _thread_handler_analizer, arguments);
}

void init_reporter_output_thread() {
    _thread_handler_arguments_t *arguments = (_thread_handler_arguments_t*) malloc(sizeof(_thread_handler_arguments_t));
    arguments->fd = fk_reporter_to_main_pipe[READ_END];
    arguments->wait_output_written = &_wait_output_written_reporter;

    _create_thread(&_reporter_output_thread, _thread_handler_reporter, arguments);
}

/* HELPER FUNCTIONS DEFINITIONS */

static void _forward_and_wait(int pipe[], bool* wait_output_written) {
    sig_wait_command_termination = true;
    write(pipe[WRITE_END], sh_last_command, strlen(sh_last_command) * sizeof(char));
    while (sig_wait_command_termination || *wait_output_written) ;
}

static void _create_thread(pthread_t* thread, void *(*thread_handler) (void *), void* arguments) {
    if (pthread_create(thread, NULL, thread_handler, arguments) != 0) {
        gn_abort("Error in creating thread", ERROR_THREAD_CREATE);
    }
}

static void *_thread_handler_analizer(void* arguments) {
    _thread_handler_arguments_t* args = (_thread_handler_arguments_t*) arguments;
    int fd = args->fd;
    bool* wait_output_written = args->wait_output_written;

    char ch;
    int read_outcome;

    do {
        *wait_output_written = false;

        do {
            read_outcome = fk_pipe_read_async(fk_analyzer_to_main_pipe[READ_END], &ch, 1);
        }
        while (read_outcome == -1);

        *wait_output_written = true;

        do {
            printf("%c", ch);
            read_outcome = fk_pipe_read_async(fk_analyzer_to_main_pipe[READ_END], &ch, 1);
        }
        while (read_outcome > 0);
    }
    while (read_outcome != 0);
}

static void *_thread_handler_reporter(void* arguments) {
    _thread_handler_arguments_t* args = (_thread_handler_arguments_t*) arguments;
    int fd = args->fd;
    bool* wait_output_written = args->wait_output_written;

    char ch;
    int read_outcome;

    do {
        *wait_output_written = false;

        do {
            read_outcome = fk_pipe_read_async(fk_reporter_to_main_pipe[READ_END], &ch, 1);
        }
        while (read_outcome == -1);

        *wait_output_written = true;

        do {
            printf("%c", ch);
            read_outcome = fk_pipe_read_async(fk_reporter_to_main_pipe[READ_END], &ch, 1);
        }
        while (read_outcome > 0);
    }
    while (read_outcome != 0);
}