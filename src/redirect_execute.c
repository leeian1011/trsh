#include "../includes/shell.h"
#include <stdio.h>

void redirect_execute(redirectcommand_t redirect){
    int pipe_filedesc[2];
    pipe(pipe_filedesc);
    pid_t pid = fork();
    
    if(pid == 0){
        close(pipe_filedesc[0]);

        dup2(pipe_filedesc[1], STDOUT_FILENO);

        execvp(redirect.program.command, redirect.program.arguments);
    }else{
    close(pipe_filedesc[1]);
        dup2(pipe_filedesc[0], STDIN_FILENO);
        char buffer[1024];
        read(STDIN_FILENO, buffer, 1024);
        buffer[strlen(buffer) - 1] = '\0';
        FILE *file = fopen(redirect.file_name, "w");

        fwrite(buffer, sizeof(char), strlen(buffer), file);
        fclose(file);
        exit(-1);
    }
    close(pipe_filedesc[0]);
    close(pipe_filedesc[1]);
    wait(NULL);
}

