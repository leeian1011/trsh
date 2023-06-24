#include "../includes/shell.h"
#include <sys/signal.h>
char *directory = NULL;
char *prompt = "> tr$h:";

void handle_interupt(int signum);
void janky_cd(char *input_buffer);
int check_cd(char *input_buffer);


int main(int argc, char **argv, char **env){
    signal(SIGINT, handle_interupt);
    int pid;
    char input_buffer[100];
    char *ls = "-la";
    char *args[] = {"-la", NULL}; 
    command_t command;
    executecommand_t exec_command;
    pipecommand_t pipe_command;
    redirectcommand_t redirect_command;
    multicommand_t multi_command;
    
    while(fgets(input_buffer, 100, stdin) >= 0){
        if(check_cd(input_buffer) == 0){
            janky_cd(input_buffer);
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
        fprintf(stdout, "tr$h (%s):", directory);   }
}

int check_cd(char *input_buffer){
    char *iterator = input_buffer;
    if(iterator[0] == 'c' && iterator[1] == 'd'){
        return 0;
    }else{ return 1;}
}

void janky_cd(char *input_buffer){
    char *iterator = input_buffer;
    while(*iterator != ' '){
        iterator++;
    }

    char *dir = iterator + 1;
    iterator += 2;

    while(*iterator != '\n'){
        iterator++;
    }

    *iterator = '\0';

    if(chdir(dir) != 0){
        fprintf(stdout, "cd: not a directory: %s\n", dir);
        fprintf(stdout, "tr$h (%s):", directory);
    }
}


void handle_interupt(int signum){
}
