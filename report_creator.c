#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

const int SIZE = 95;

int main(void) {
    puts("Server - listening");

    //Create fifo
    int code = mkfifo("/tmp/demo6_fifo", 0666);
    if (code == -1) {
        perror("mkfifo returned an error - file may already exist");
    }

    //Open read end
    int fd = open("/tmp/demo6_fifo", O_RDONLY);
    if (fd == -1) {
        perror("Cannot open FIFO for read");
        return EXIT_FAILURE;
    }
    puts("FIFO OPEN");

    int data[SIZE];
    read(fd, data, sizeof(int)*SIZE);


    int i ;
    for(i = 0; i < SIZE; i++){
        printf("%c - %d \n", (char)(i+32), data[i]);
    }



    puts("EOF found");

    //Tidy up
    close(fd);
    puts("FIFO Closed");
    unlink("/tmp/demo6_fifo");
    puts("FIFO Removed");

    return EXIT_SUCCESS;
}