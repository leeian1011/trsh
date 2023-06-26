#include "../includes/shell.h"

static char *parse_directory(char *new_directory){

    char *iterator = new_directory;
    
    while(*iterator != '\0'){
        iterator++;
    }

    char *reverse_iterator = iterator;
    while(*reverse_iterator != '/'){
        reverse_iterator--;
    }
    char *new_dir = malloc(strlen(reverse_iterator) + 1);

    strcpy(new_dir, reverse_iterator);
    return new_dir;
}


const user_interface construct_ui(){
    user_interface prompt;
    prompt.prompt = "tr$h :";
    prompt.directory = NULL;
    return prompt;
}

char *update_directory(){
    char raw_directory[1024];
    getcwd(raw_directory, 1024);
    raw_directory[strlen(raw_directory) + 1] = '\0';
    char *ndirectory = parse_directory(raw_directory);
    
    return ndirectory;
}
    

