#include "../includes/shell.h"

redirectcommand_t parse_redirect(char *input_buffer){
    redirectcommand_t redirect;
    char *iterator = input_buffer;
    while(*iterator != '<' && *iterator != '>'){
        iterator++;
    }
    
    *(iterator -1) = '\n';
    if(*iterator == '>'){
        redirect.redirect_type = REDIRECT_OUTPUT;
    }else{
        redirect.redirect_type = REDIRECT_INPUT;
    }

    redirect.program = parse_execute(input_buffer);
    
    while(*iterator == ' ' || *iterator == '>' || *iterator == '<'){
        iterator++;
    }
    char *file_name = iterator;
    if(*file_name == '\n'){
        redirect.file_name = "does not compute my friend";
        return redirect;
    }
    while(*iterator != '\n'){
        iterator++;
    }
    
    *iterator = '\0';

    redirect.file_name = file_name;

    return redirect;
}
