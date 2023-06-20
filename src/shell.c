#include "../includes/shell.h"


int main(int argc, char **argv, char **env){
    char input_buffer[100];
    char *ls = "-la";
    char *args[] = {"-la", NULL}; 
    command_t command;
    executecommand_t exec_command;
    pipecommand_t pipe_command;
    redirectcommand_t redirect_command;
    multicommand_t multi_command;

    fprintf(stdout, "tr$h (%s):", "test");
    while(fgets(input_buffer, 100, stdin) >= 0){
        command = parse_type(input_buffer);
        switch(command.type){
            case EXECUTE:
                exec_command = parse_execute(input_buffer); 
                if(fork() == 0){
                    execvp(exec_command.command, exec_command.arguments); 
                }else{
                    wait(NULL);
                }
            case MULTI:

            break;
            default:
                break;
        }
   }
}

