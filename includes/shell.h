#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARGS 10
#define OPERAND_COUNT 5


typedef struct{
    int type[OPERAND_COUNT];
    char symbol[OPERAND_COUNT];
}operands_t;

enum operands{ NO_COMMAND = -1,
               EXECUTE,
               PIPE,
               REDIRECT,
               MULTI,
             };


typedef struct{
    char *directory;
    const char *prompt;
}user_interface;


typedef struct{
    int type;
}command_t;


typedef struct{
    char *command;
    char *(*arguments);
    int argument_counter;
}executecommand_t;

enum exec_code{ SUCCESS,
                ERROR,
              };


typedef struct{
    executecommand_t left;
    executecommand_t right;
}pipecommand_t;

enum pipe_code{ PIPE_SUCCESS,
                PIPE_ERROR,
              }; 


typedef struct{
    int redirect_type;
    char *file_name;
    executecommand_t program;
}redirectcommand_t;

enum redirect_type{ REDIRECT_INPUT,
                    REDIRECT_OUTPUT,
                  };

enum redirect_code{ REDIRECT_SUCCESS,
                    REDIRECT_ERROR,
                  };

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
enum pipe_code pipe_execute(pipecommand_t pipe_command);

//redirect parsing
redirectcommand_t parse_redirect(char *input_buffer);
enum redirect_code redirect_execute(redirectcommand_t redirect);
//user_interface
const user_interface construct_ui();
char *update_directory();

#endif 
