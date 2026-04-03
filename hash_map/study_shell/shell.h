#ifndef SHELL_H
#define SHELL_H

void get_input(char* input, char* commands[100][100]);
void command_launch(char* commands[100][100]);
int handle_builtin(char* commands[100][100]);

#endif