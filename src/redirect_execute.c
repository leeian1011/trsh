#include "../includes/shell.h"

static enum redirect_code execute_output(redirectcommand_t redirect){
    int pipe_filedesc[2];
    pipe(pipe_filedesc);
    pid_t pid = fork();

    if(pid == 0){
        pid_t pid2 = fork();
        if(pid2 == 0){
            close(pipe_filedesc[0]);

            dup2(pipe_filedesc[1], STDOUT_FILENO);
            if(execvp(redirect.program.command, redirect.program.arguments) == -1){
                fprintf(stderr, "tr$h: command not found : %s\n", redirect.program.command);
                exit(ERROR);
            }
        }else{
            close(pipe_filedesc[1]);
            dup2(pipe_filedesc[0], STDIN_FILENO);

            char buffer[1024];
            read(STDIN_FILENO, buffer, 1024);
            buffer[strlen(buffer) - 1] = '\n';
            FILE *file = fopen(redirect.file_name, "w");
            fprintf(file, "%s", buffer);
            fclose(file);
            exit(REDIRECT_SUCCESS);
        }
    }else{
        close(pipe_filedesc[0]);    
        close(pipe_filedesc[1]);
        wait(NULL);
    }
    return(REDIRECT_SUCCESS);
}


static enum redirect_code execute_input(redirectcommand_t redirect){
    int pipe_filedesc[2];
    pipe(pipe_filedesc);

    pid_t pid = fork();
    if(pid == 0){
        pid_t pid2 = fork();
        if(pid2 == 0){
            close(pipe_filedesc[0]);

            dup2(pipe_filedesc[1], STDOUT_FILENO);
            FILE *file = fopen(redirect.file_name, "r");
            if(file == NULL){
                exit(REDIRECT_ERROR);
            }
            char buffer[1024];
            fread(buffer, 1024, sizeof(char), file);
            buffer[strlen(buffer) - 1] = '\0';

            fclose(file);
            write(STDOUT_FILENO, buffer, strlen(buffer));
            exit(PIPE_SUCCESS);
        }else{
            close(pipe_filedesc[1]);

            dup2(pipe_filedesc[0], STDIN_FILENO);
            execvp(redirect.program.command, redirect.program.arguments);
        }
    }else{
        close(pipe_filedesc[0]);
        close(pipe_filedesc[1]);
        wait(NULL);
    }
    return(REDIRECT_SUCCESS);
}


enum redirect_code redirect_execute(redirectcommand_t redirect){
    return redirect.redirect_type == REDIRECT_OUTPUT ? execute_output(redirect) : execute_input(redirect);
}



















