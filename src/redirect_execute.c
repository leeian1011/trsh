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
            int buffer_size = 1024;
            int bytes_read = 0;
            int total_bytes = 0;
            close(pipe_filedesc[1]);
            dup2(pipe_filedesc[0], STDIN_FILENO);
            char *buffer = malloc(buffer_size);
            if(buffer == NULL){
                exit(-1);
            }

            while((bytes_read = read(pipe_filedesc[0], buffer + total_bytes, buffer_size - total_bytes)) > 0){
                total_bytes += bytes_read;
                if(total_bytes == buffer_size){
                buffer_size*=2;}
                buffer = realloc(buffer, buffer_size);
            }

            buffer[strlen(buffer) - 1] = '\n';
            FILE *file = fopen(redirect.file_name, "w");
            fprintf(file, "%s", buffer);
            free(buffer);
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
            char c;
            fseek(file, 0, SEEK_END);
            int file_size = ftell(file);
            fseek(file, 0, SEEK_SET);
            rewind(file);
            char *buffer = malloc(file_size);
            fread(buffer, file_size, sizeof(char), file);

            fclose(file);
            write(STDOUT_FILENO, buffer, file_size);
            free(buffer);
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



















