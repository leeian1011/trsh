#include "../includes/shell.h"

void pipe_execute(pipecommand_t pipe_command){
    int pipe_filedescriptors[2];
    if(pipe(pipe_filedescriptors) == -1){
        fprintf(stderr, "big file descriptor no no\n");
        exit(-1);
    }
    pid_t pid = fork();

    if(pid == 0){
        pid_t pid_2 = fork();
        if(pid_2 == 0){
            close(pipe_filedescriptors[0]);

            dup2(pipe_filedescriptors[1], STDOUT_FILENO);
            if(execvp(pipe_command.left.command, pipe_command.left.arguments) == -1){
                close(pipe_filedescriptors[1]);
                fprintf(stderr, "command not found: %s\n", pipe_command.left.command);
                exit(-1);
            }
        }else{
            close(pipe_filedescriptors[1]);

            dup2(pipe_filedescriptors[0], STDIN_FILENO);
            if(execvp(pipe_command.right.command, pipe_command.right.arguments) == -1){
                close(pipe_filedescriptors[0]);
                fprintf(stderr, "command not found : %s\n", pipe_command.right.command);
                exit(-1);
            }
        }
    }else{
        close(pipe_filedescriptors[0]);
        close(pipe_filedescriptors[1]);
        wait(NULL);
    }
}
