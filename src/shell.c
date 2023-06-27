#include "../includes/shell.h"

int janky_exit(char *input_buffer){
    char *exit = "exit";
    char tmpholder;
    char *iterator = input_buffer;
    while(*iterator != ' ' && *iterator != '\n'){ iterator++; }
    tmpholder = *iterator;
    *iterator = '\0';
    if(strcmp(input_buffer, exit) == 0){ return(1); }

    *iterator = tmpholder;
    return(0);
}

int main(int argc, char **argv, char **env){
    int pid;
    char input_buffer[100];
    command_t command;
    executecommand_t exec_command;
    pipecommand_t pipe_command;
    redirectcommand_t redirect_command;
    multicommand_t multi_command;
    user_interface ui = construct_ui(); 
    ui.directory = update_directory(); 

    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    while(fgets(input_buffer, 100, stdin) >= 0){
        if(janky_exit(input_buffer)){ exit(-1); }

        if(check_cd(input_buffer)){
            change_dir(input_buffer, &ui);
            continue;
        }

        command = parse_type(input_buffer);

        switch(command.type){
            case EXECUTE:
                pid = fork();
                if(pid == 0){
                    exec_command = parse_execute(input_buffer);
                    execvp(exec_command.command, exec_command.arguments); 
                }
                else{ wait(NULL); }
                break;
            case MULTI:
                printf("Multi reached\n");
            break;
            default:
                printf("Default reached\n");
                break;
        }
    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    }

    return(0);
}

