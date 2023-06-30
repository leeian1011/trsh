#include "../includes/shell.h"

pipecommand_t parse_pipe(char *input_buffer){
    pipecommand_t pipe;
    char *left_string;
    char *right_string;
    char *iterator = input_buffer;
    while(*iterator != '|'){
        iterator++;
    }
    left_string = input_buffer;
    right_string = input_buffer;

    while(*right_string != '|'){
       if(*(right_string + 1) == '|'){
           *right_string = '\n';
           pipe.left = parse_execute(left_string);
           break;
        }
      right_string++;
    } 

    while(*iterator == ' ' || *iterator == '|'){
        iterator++;
    }

    right_string = iterator;
    while(*iterator != '\n'){
        iterator++;
    }
    pipe.right = parse_execute(right_string);
   
    return pipe;
}

