#include "../includes/shell.h"

enum pipe_code pipe_execute(pipecommand_t pipe_command){
    int pipe_filedesc[2];
    if(pipe(pipe_filedesc) == -1){
        fprintf(stderr, "pipe error\n");
        exit(PIPE_ERROR);
    }
    pid_t pid = fork();

    if(pid == 0){
        pid_t pid_2 = fork();
        if(pid_2 == 0){
            close(pipe_filedesc[0]);

            dup2(pipe_filedesc[1], STDOUT_FILENO);
            if(execvp(pipe_command.left.command, pipe_command.left.arguments) == -1){
                close(pipe_filedesc[1]);
                fprintf(stderr, "command not found: %s\n", pipe_command.left.command);
                exit(PIPE_ERROR);
            }
        }else{
            close(pipe_filedesc[1]);

            dup2(pipe_filedesc[0], STDIN_FILENO);
            if(execvp(pipe_command.right.command, pipe_command.right.arguments) == -1){
                close(pipe_filedesc[0]);
                fprintf(stderr, "command not found: %s\n", pipe_command.right.command);
                exit(PIPE_ERROR);
            }
        }
    }else{
        close(pipe_filedesc[0]);
        close(pipe_filedesc[1]);
        wait(NULL);
    }
    return (PIPE_SUCCESS);
}
