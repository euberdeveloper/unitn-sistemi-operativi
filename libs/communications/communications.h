
#ifndef SOLVER_COMUNICATIONS_H
#define SOLVER_COMUNICATIONS_H

#include "../general/general.h"
#include "../util/util.h"


// NORMALS
void send_to_parent_p(char *path, unsigned long long *vect, int *fd);
void send_to_parent_c(char *path, unsigned long long *vect, int *fd);
char *next_path(int *fd);
range next_range(int *fd);
void send_path(char *path, int *fd);
void send_range(range range, int *fd);

// THREADS
void *receiver_c(void *args);
void *receiver_p(void *args);


#endif //SOLVER_COMUNICATIONS_H
