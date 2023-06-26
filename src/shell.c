#include "../includes/shell.h"

void janky_exit(char *input_buffer){
    char *iterator = malloc(strlen(input_buffer) + 1);
    if(iterator == NULL){
        exit(1);
    }

    strcpy(iterator, input_buffer);
    char *check = iterator;
    while(*iterator != ' ' && *iterator != '\n'){
        iterator++;
    }
    *iterator = '\0';
    if(strcmp(check, "exit") == 0){
        exit(1);
    }
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
        janky_exit(input_buffer);
        if(check_cd(input_buffer) == 1){
            change_dir(input_buffer, &ui);
            continue;
        }
        command = parse_type(input_buffer);
        switch(command.type){
            case EXECUTE:
                
                pid = fork();
                exec_command = parse_execute(input_buffer);
                printf("%s\n", exec_command.command);
                for(int i = 0; i < 10; i++){
                    printf("%s\n", exec_command.arguments[i]);
                }
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
    printf("end of loop\n");
    fprintf(stdout, "%s %s", ui.directory, ui.prompt);
    }
}

