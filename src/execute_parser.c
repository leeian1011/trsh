#include "../includes/shell.h"


static int argument_count(char *input_buffer){
    char *iterator = input_buffer;
    int count = 1;

    while(*iterator != '\0' && *iterator != '\n'){
        if(*iterator == ' '){ count++; }
        iterator++;
    }

    return(count);
}


executecommand_t parse_execute(char *input_buffer){
    executecommand_t execute;
    int count = argument_count(input_buffer);
    execute.arguments = malloc(count * sizeof(char *));
    if(execute.arguments == NULL){
        fprintf(stderr, "Memory Err\n");
        exit(-1);
    }

    int arg_index = 1;
    char *iterator = input_buffer;
    char *argument_pointer = NULL;
    while(*iterator != ' ' && *iterator != '\n'){ iterator++; }

    *iterator = '\0';
    execute.command = input_buffer;
    execute.arguments[0] = input_buffer;
    if(count == 1){ return(execute); }

    argument_pointer = iterator + 1;
    iterator = iterator + 1;
    while(*iterator != '\n'){
        if(*iterator == ' '){
            *iterator = '\0';
            execute.arguments[arg_index] = malloc(strlen(argument_pointer) + 1);
            if(execute.arguments[arg_index] == NULL){
                fprintf(stderr, "Memory Err\n");
                free(execute.arguments);
                exit(-1);
            }
            strcpy(execute.arguments[arg_index++], argument_pointer);
            argument_pointer = iterator + 1;
            iterator = iterator + 1;
        }
        iterator++;
    }

    if(*iterator == '\n'){
        *iterator = '\0';
        execute.arguments[arg_index] = malloc(strlen(argument_pointer) + 1);
        if(execute.arguments[arg_index] == NULL){
            fprintf(stderr, "memory err\n");
            free(execute.arguments);
            exit(-1);
        }
        execute.arguments[arg_index++] = argument_pointer;
    }
    return(execute);
}









