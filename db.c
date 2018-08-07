//
// Created by Kelvin Wahome on 8/7/18.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * InputBuffer as a small wrapper around the state we need to store to interact with getline()
 */
struct InputBuffer_t {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

typedef struct InputBuffer_t InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

/*
 * Prints a prompt to the user.
 * We do this before reading each line of input
 */

void print_prompt() { printf("db > "); }

/*
 * Read a line of input
 * We tell getline to store the read line in input_buffer->buffer and the size of the allocated buffer in input_buffer->buffer_length.
 * We store the return value in input_buffer->input_length.
 * buffer starts as null, so getline allocates enough memory to hold the line of input and makes buffer point to it.
 */
void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read =
            getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

/*
 * Starts a read-execute-print loop when you start it from the command line
 * Infinite loop that prints the prompt, gets a line of input, then processes that line of input
 */
int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
    }
}
