#include "../includes/shell.h"

int check_cd(char *input_buffer){
    return (input_buffer[0] == 'c' && input_buffer[1] == 'd');
}


void change_dir(char *input_buffer, user_interface *ui){
    char *iterator = input_buffer;
    char *newdir = NULL;

    while(*iterator != ' ' && *iterator != '\n'){
        iterator++;
    }

    if(*iterator == '\n'){
        char *home = getenv("HOME");
        chdir(home);
        free(ui->directory);
        ui->directory = update_directory();
        fprintf(stdout, "%s %s", ui->directory, ui->prompt);
        return;
    }
    
    newdir = ++iterator;

    while(*iterator != '\n'){
       iterator++;
    }

    *iterator = '\0';

    if(chdir(newdir) != 0){
        fprintf(stdout, "cd : not a directory : %s\n", newdir);
        fprintf(stdout, "%s %s", ui->directory, ui->prompt);
        return;
    }
    free(ui->directory);
    ui->directory = update_directory();
    fprintf(stdout, "%s %s", ui->directory, ui->prompt);
}

