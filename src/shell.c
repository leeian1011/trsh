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
    pid_t pid;
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
                exec_command = parse_execute(input_buffer);
                pid = fork();
                if(pid == 0){
                    if(execvp(exec_command.command, exec_command.arguments) == -1){
                        fprintf(stderr, "tr$h : command not found : %s\n", exec_command.command);
                        exit(ERROR);
                    }
                }else{
                    wait(NULL); 
                }
                free(exec_command.arguments);
                break;
            case PIPE:
                pipe_command = parse_pipe(input_buffer);
                pipe_execute(pipe_command);
                free(pipe_command.left.arguments);
                free(pipe_command.right.arguments);
                break;
            case REDIRECT:
                redirect_command = parse_redirect(input_buffer);
                redirect_execute(redirect_command);
                free(redirect_command.program.arguments);
                break;
            case MULTI:
                printf("Multi reached\n");
            break;
            default:
                printf("Default reached\n");
                break;
        }
    input_buffer[0] = '\n';
    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    }

    return(0);
}

