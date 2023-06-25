#include "../includes/shell.h"


int main(int argc, char **argv, char **env){
    int pid;
    char input_buffer[100];
    command_t command;
    executecommand_t exec_command;
    pipecommand_t pipe_command;
    redirectcommand_t redirect_command;
    multicommand_t multi_command;
    user_interface ui = ui_init(); 
    ui.directory = update_directory();
    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    while(fgets(input_buffer, 100, stdin) >= 0){
        if(check_cd(input_buffer) == 1){
            change_dir(input_buffer, &ui);
            continue;
        }
        command = parse_type(input_buffer);
        switch(command.type){
            case EXECUTE:
                pid = fork();
                exec_command = parse_execute(input_buffer); 
                if(pid == 0){
                    execvp(exec_command.command, exec_command.arguments); 
                }
                wait(NULL);
                break;
            case MULTI:

            break;
            default:
                break;
        }
    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    }
}

