#include "../includes/shell.h"

const operands_t construct_operands(){
    operands_t operands;
    char symbols[] = {'|', '<', '>'}; 
    for(int i = 0; i < 3; i++){
        operands.symbol[i] = symbols[i];
    }

    for(int i = 1; i < 3; i++){
        operands.type[i-1] = i;
        if(i == 2){ operands.type[i] = REDIRECT; }
    }

    return(operands);
}

int is_operand(char current_pointer, operands_t operand){
    for(int i = 0; i < 3; i++){
        if(current_pointer == operand.symbol[i]){ return(operand.type[i]); }
    }
    
    return(0);
}
    
