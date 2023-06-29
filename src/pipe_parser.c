#include "../includes/shell.h"

pipecommand_t parse_pipe(char *input_buffer){
    printf("INPUT: %s\n", input_buffer);
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
           printf("LEFT STRING: %s\n", left_string);
           pipe.left = parse_execute(left_string);
           break;
        }
      right_string++;
    } 

    printf("LEFT COMMAND: %s\n", pipe.left.command);
    printf("LEFT ARGUMENTS: \n");
    for(int i = 0; i < pipe.left.argument_counter; i++){
        printf("%s\n", pipe.left.arguments[i]);
    }
    while(*iterator == ' ' || *iterator == '|'){
        iterator++;
    }

    right_string = iterator;
    while(*iterator != '\n'){
        iterator++;
    }
    printf("RIGHT STRING: %s\n", right_string);
    pipe.right = parse_execute(right_string);
   
    printf("RIGHT COMMAND: %s\n", pipe.right.command);
    printf("RIGHT ARGUMENTS: \n");
    for(int i = 0; i < pipe.right.argument_counter; i++){
        printf("%s\n", pipe.right.arguments[i]);
    }
    return pipe;
}

