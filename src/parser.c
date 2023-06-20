#include "../includes/shell.h"

command_t parse_type(char *input_buffer){
    const operands_t operand = construct_operands();
    command_t command;
    int operand_value;
    int operand_count = 0;
    char *iterator = input_buffer;

    while(*iterator != '\0' && *iterator != '\n'){
        if((operand_value = is_operand(*iterator, operand)) != 0){
            if(operand_count > 0){
                command.type = MULTI;
                return command;
            }
            command.type = operand_value;
            operand_count++;
        }
        iterator++;
    }

    if(operand_count == 0){
        command.type = EXECUTE;
    }

    return command;
}

executecommand_t parse_execute(char *input_buffer){
    executecommand_t execute;
    int arg_index = 0;
    char *iterator = input_buffer;
    char *argument_pointer = NULL;
    while(*iterator != ' ' && *iterator != '\n'){
        iterator++;
    }

    if(*iterator == '\n'){
        *iterator = '\0';
        execute.command = input_buffer;
        for(int i = 0; i < MAX_ARGS; i++){
            if(i == 0){
                execute.arguments[i] = execute.command;
                continue;
            }
            execute.arguments[i] = NULL;
        }
        return execute;
    }
    
    *iterator = '\0';
    execute.command = input_buffer;
    execute.arguments[arg_index++] = input_buffer;
    argument_pointer = iterator + 1;
    iterator = iterator + 1;
    while(*iterator != '\n'){
        if(*iterator == ' '){
            *iterator = '\0';
            execute.arguments[arg_index++] = argument_pointer;
            argument_pointer = iterator + 1;
            iterator = iterator + 1;
        }
        iterator++;
    }
    if(*iterator == '\n'){
        *iterator = '\0';
        execute.arguments[arg_index++] = argument_pointer;
    }
    
    for(int i = arg_index; i < MAX_ARGS; i++){
        execute.arguments[i] = NULL;
    }

    return execute;
}









