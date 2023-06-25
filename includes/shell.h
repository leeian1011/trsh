#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10

#define TYPE_COUNT 5
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
    char *arguments[MAX_ARGS];
    void (*function)(int);
}executecommand_t;

typedef struct{
    int type;
}pipecommand_t;

typedef struct{

}redirectcommand_t;

typedef struct{

}multicommand_t;

//builtin_cd.c
int check_cd(char *user_input);
void change_dir(char *user_input, user_interface *ui); 

//operands_t 
const operands_t construct_operands();
int is_operand(char current_pointer, operands_t operands);

//parser
command_t parse_type(char *input_buffer);
executecommand_t parse_execute(char *input_buffer);

//user_interface
user_interface ui_init();
char *update_directory();

#endif 
