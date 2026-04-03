#include "shell.h"
#include <stdio.h>


int main(){

    char input[100]; 
    char* commands[100][100];

    while(1){
        commands[0][0] = NULL;
        get_input(input, commands);
        if(commands[0][0] == NULL || handle_builtin(commands)) continue;
        command_launch(commands);
    }

    return 0;
}