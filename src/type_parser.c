#include "../includes/shell.h"


command_t parse_type(char *input_buffer){
    const operands_t operand = construct_operands();
    command_t command;
    int operand_value;
    int operand_count = 0;
    int character_count = 0;
    char *iterator = input_buffer;
    if(*iterator == '\n'){
        command.type = NO_COMMAND;
        return(command);
    } 

    while(*iterator != '\n'){
        if((operand_value = is_operand(*iterator, operand)) != 0){
            if(operand_count > 0){
                command.type = MULTI;
                return(command);
            }
            command.type = operand_value;
            operand_count++;
        }
        iterator++;
        character_count++;
    }

    if(operand_count == 0){
        command.type = EXECUTE;
    }

    return(command);
}
