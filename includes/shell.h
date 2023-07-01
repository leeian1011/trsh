#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10

#define TYPE_COUNT 5
#define NO_COMMAND -1
#define EXECUTE 0
#define PIPE 1
#define REDIRECT 2
#define MULTI 3

typedef struct{
    char *directory;
    const char *prompt;
}user_interface;

typedef struct{
    int type[TYPE_COUNT];
    char symbol[TYPE_COUNT];
}operands_t;

typedef struct{
    int type;
}command_t;

typedef struct{
    char *command;
    char *(*arguments);
    int argument_counter;
}executecommand_t;

typedef struct{
    executecommand_t left;
    executecommand_t right;
}pipecommand_t;
    
typedef struct{
    char *file_name;
    executecommand_t program;
}redirectcommand_t;

typedef struct{

}multicommand_t;

//builtin_cd.c
int check_cd(char *user_input);
void change_dir(char *user_input, user_interface *ui); 

//operands_t 
const operands_t construct_operands();
int is_operand(char current_pointer, operands_t operands);

//parsers
//type-parsing
command_t parse_type(char *input_buffer);

//execute command parsing
executecommand_t parse_execute(char *input_buffer);
void free_execute(executecommand_t *execute);

//pipe parsing
pipecommand_t parse_pipe(char *input_buffer);
void pipe_execute(pipecommand_t pipe_command);

//redirect parsing
redirectcommand_t parse_redirect(char *input_buffer);

//user_interface
const user_interface construct_ui();
char *update_directory();

#endif 
