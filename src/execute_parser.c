#include "../includes/shell.h"


static int argument_count(char *input_buffer){
    char *iterator = input_buffer;
    int count = 1;

    while(*iterator != '\0' && *iterator != '\n'){
        if(*iterator == ' '){ count++; }
        iterator++;
    }

    return (count);
}

executecommand_t parse_execute(char *input_buffer){
    executecommand_t execute;
    execute.argument_counter = argument_count(input_buffer); 
    execute.arguments = malloc(execute.argument_counter * sizeof(char *));
    if(execute.arguments == NULL){
        fprintf(stderr, "Memory Err\n");
        exit(-1);
    }

    int arg_index = 0;
    char *iterator = input_buffer;
    char *argument_pointer = NULL;
    while(*iterator != ' ' && *iterator != '\n'){ iterator++; }

    *iterator = '\0';
    execute.command = input_buffer;
    execute.arguments[arg_index++] = input_buffer;;
    if(execute.argument_counter == 1){ return(execute); }
    
    argument_pointer = ++iterator;

    while(*iterator != '\n'){
        if(*iterator == ' '){
            *iterator = '\0';
            execute.arguments[arg_index++] = argument_pointer;
            argument_pointer = ++iterator;
        }
        iterator++;
    }
    
    *iterator = '\0';
    execute.arguments[arg_index] = argument_pointer;

    for(int i = 0; i < execute.argument_counter; i++){
        printf("%s\n", execute.arguments[i]);
    }
    return(execute);
}









