#include "shell.h"

int main(void){
    char c = 'Y';
    char x = '\n';
    write(1, &c, 1);
    write(1, &x, 1);
}
