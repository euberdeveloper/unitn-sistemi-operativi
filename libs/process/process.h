//
// Created by xeno on 08/06/20.
//

#ifndef SOLVER_PROCESS_H
#define SOLVER_PROCESS_H

#include "../general/general.h"
#include "../communication/communication.h"
#include <pthread.h>

#include "../util/util.h"
#include "../communications/communications.h"

process create_c(int p_number, int q_number,files_array *files);

void GrandsonJob(char* text, int fd[2]);
void SonJob(char* text, int fd[2]);
char *strcut(const char *string,unsigned int start,unsigned int length);
char *getText();


#endif //SOLVER_PROCESS_H
