## TRash SHell  

While working on [dash](https://github.com/leeian1011/dsh) I learnt a lot about how the shell works and also about
child processes and why certain programs can be made externally and why some are built-in, most of them tend to be performance issues
but others are process logic issues like 'cd'!

I've decided to make a mini simple shell that imitates the behaviour of typical shells like bash from scratch with C to further my understanding!

## DEMO
![demo of shell running](https://github.com/leeian1011/trsh/blob/main/demos/shelldemo.gif)

> Demo of most up to date functionality.

## Side Notes
Before making this I learnt a bit about OOP with Java but it didnt really click but using [this](https://www.youtube.com/watch?v=ubt-UjcQUYg&t=684s)
as a reference and without copying entirely one for one, I understand better why OOP is likeable, having methods making this would help a lot.

Working with strings really help me understand pointers even more with how you can technically traverse back-to-back memory addresses
the same way you would traverse a linked list in C!

Despite knowing this, I feel that indexing into a `char *` with '/[x]' syntax is much better and more readable honestly.

So I was messing around with the shell trying all sort of edge cases and one particular one came up. When running "grep ls", the process
loops on forever, which is to be expected, but when I force quit with `ctrl + c`, it terminates the shell process altogether and returns me to 
my original zsh shell, so a simple search online tells me about the `sys/signal.h` library and how certain signals have to be handled.

What nobody I've ever seen mentioned was that the `signal()` function accepts a whole function as an argument ???
FUNCTION POINTERS ??? WHAT ??? 

`void (*signal(int signum, void (*handler)(int)))(int);`
This doesnt JUST accepts a function pointer it RETURNS ONE

- Some thing interesting i learnt is in the exit built-in function, since i pass in a pointer to the input_buffer, altering the memory
addresses with an iterator pointer affects the actual memory location, we get a copy of the pointer not a copy of the memory address 
in the function.

- If you malloc memory to an iterator, you have to assign another pointer to the first memory location, kinda like moving responsibility
to the new pointer before you iterate through the memory addresses with the iterator pointer.

## Processes & Exit 

- Had some issues with getting exit to work, originally noticed that a bug would occur whereby, if '\n' was inputted 'x' times, it would take
'x + 1' times before exit would work. Managed to solve it by making sure the input pointer's first memory location is set to '\0'.

- The exact same bug behaviour is displayed when I input a program name that does not exist. Realized that both the earlier fix and the current
issue had the exact same problem and that it was not because there was still commands in the input_buffer. The problem was that I had greatly
misunderstood the usage of `fork()`. I've mistaken `fork()`'s functionality with `execvp()`'s functionality. I assumed that when `execvp()`
is ran, the process image is replaced and it automatically kills the child process, but that is wrong. It is still a child process, it's just 
running a different program.

- When an input appears where the command does not exist, `fork()` creates a child process, but because `execvp()` does not successfully run 
the process image is not replaced, and the child process is never terminated.

``` C
command = parse_type(input_buffer);
switch(command.type){
    case EXECUTE:
        pid = fork();
        exec_command = parse_execute(input_buffer);
        if(pid == 0){
            if(execvp(exec_command.command, exec_command.arguments) == -1){
                fprintf(stderr, "tr$h : command not found : %s\n", exec_command.command);
                // exit(-1) is suppose to go here.
            }
        }else{
            wait(NULL); 
        }
        free(exec_command.arguments);
        break;
    case MULTI:
        printf("Multi reached\n");
        break;
    default:
        printf("Default reached\n");
        break;
}
```
- The code example above is the original version that led to the bug. Seeing as execvp does not change the process image, and the new 
program essentially does not "terminate" or "exit" the parent process is eternally waiting for the child process to terminate.
The child process proceeds on with the code, and continues the loop. The bug is essentially exiting the subprocess and returning to the parent
process.

> Quite a janky bug but learnt a lot from this!


## PIPES

The good ol' pipe, trying to get two programs, or two processes even, to communicate with one another.
`pipe(int filedes[2])` creates pipe filedescriptors for read and writes, essentially just an input output stream socket.
We have to use `dup2()` in order to paste the stdout and stdin file descriptors onto the read and write streams of the pipe.

It's not exactly like a socket, but its eerily similar and it helps me understand much better. It's a lot of redirecting io around.

- Had an issue whereby after every second input that involes a pipe, a seg fault occurs, turns out there was an error on how I was parsing
the user input.

- When creating the right-side command, I accidentally set the '\n' character to '\0' before I call `parse_execute()` on it.

- This causes `parse_execute()` to continuously cycle through memory addresses and causes a segfault.

## REDIRECTION

Read up about enums and how they allow better readability, will attempt to learn how to use them by implementing enums in the program.
Learnt something really cool!

- When using `fgets()` what ends up happening is that the function reads from the input source up until it reachs a '\n' character.
This caused a bug where attempting to use `fgets()` on the output of the command `ls` causes a problem whereby it only reads upto 
the first directory/file present! This causes issues when trying to read to a buffer thats 1024 bytes big leading to lots of unfilled 
memory address and leading to undefined behaviour.

- Learnt about how pointer arithmetic can help with working around reading unknown size of data.
Combining offset of data read, and data to be read, along with realloc allows us to read unknown size of data.







