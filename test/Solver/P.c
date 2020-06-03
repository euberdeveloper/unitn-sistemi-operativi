#include "../util/util.h"

int main(int argc, char *argv[]){
    int i, index = 2,m = 5;
    bool shell = false, rec = false;
    data_inputs input;

    parse_arguments(argc, argv, &index, &m, &input, &shell, &rec);

    pthread_t A_sender, A_receiver, C_receiver;

    pthread_analyzer_arguments args;
    args.path = concat("/tmp/P",to_string(index));
    pthread_create(&A_sender, NULL, pthread_fd_analyzer_sender, (void*)&args );

    pthread_join(A_sender, NULL);

    return 0;
}