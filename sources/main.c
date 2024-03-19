#include "step1.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  // disable printf buffering for stdout.
  // do not remove please.
    setvbuf(stdout, NULL, _IONBF, 0);

    char buffer[MAX_COMMAND_LENGTH + 1] = {0};
    int status = 0;
    int buffer_index = 0;

    do {
    status = read(0, buffer + buffer_index, 1); // read one character at a time

    if (status == -1) {
        perror("read()");
        return EPI_EXIT_FAILURE;
    } else if (status == 0) {
        return EPI_EXIT_SUCCESS;
    } else {
      if (buffer[buffer_index] == '\n') { // if newline is encountered, process the command
        if (on_command(buffer) == false) {
        return EPI_EXIT_FAILURE;
        }
        memset(buffer, 0, MAX_COMMAND_LENGTH); // clear the buffer
        buffer_index = 0; // reset the buffer index
        } else {
        buffer_index++; // increment the buffer index}
    }
    } while (status);
    return EPI_EXIT_SUCCESS;
}
