#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void get_input(char* input, char* commands[100][100]){

    printf("myshell> ");
    if(fgets(input, 100, stdin) == NULL){
        printf("could not get an input\n");
        return;
    }

    input[strcspn(input, "\n")] = 0;

    int i = 0, j = 0;
    char* token = strtok(input, "|");
    char* pipe_division[100];

    while(token != NULL){
        pipe_division[i++] = token;
        token = strtok(NULL, "|");
    }
    pipe_division[i] = NULL;
  

    if(pipe_division[0] == NULL){
        commands[0][0] = NULL;
        return;
    }

    char** element = pipe_division;
    char* token2;
    i = 0;
    while(*element != NULL){
        token2 = strtok(*element, " ");

        if(*token2 == '\0') {
            element++;
            continue;
        }

        j = 0;
        while(token2 != NULL){
            commands[i][j++] = token2;
            token2 = strtok(NULL, " ");
            if(j == 99) break;
        }
        commands[i++][j] = NULL; 
        element++;
        if(i == 99) break;
    }
    commands[i][0] = NULL;

}


void command_launch(char* commands[100][100]){

    if(commands[1][0] == NULL){

    pid_t my_pid = fork();
    if(my_pid < 0){
        printf("Error in process forking\n");
        return;
    }

    if(my_pid){
        waitpid(my_pid, NULL, 0);
    }

    if(my_pid == 0){
        execvp(commands[0][0],commands[0]);
        perror("Exec failed");
        exit(1);
    }
}

else{

    int pipes[100][2];
    
    int i = 0;
    pid_t pid;

    while(commands[i + 1][0] != NULL){
        if(pipe(pipes[i]) < 0){
            perror("pipes");
            return;
        }
        i++;
    }

    i = 0;

    while(commands[i][0] != NULL){
        pid = fork();
        
        if(pid < 0){
            printf("fork failed\n");
            return;
        }

        if(pid == 0){
            if(i > 0){
                dup2(pipes[i - 1][0], 0);
            }
            if(commands[i + 1][0] != NULL){
                dup2(pipes[i][1], 1);
            }

            for(int k = 0; commands[k + 1][0] != NULL; k++){
                close(pipes[k][0]);
                close(pipes[k][1]);
            }

            execvp(commands[i][0], commands[i]);
            fprintf(stderr, "%s: command failed\n", commands[i][0]);
            exit(1);
        }
        i++;
    }

    for(i = 0; commands[i + 1][0] != NULL; i++){
        close(pipes[i][1]);
        close(pipes[i][0]);
    }

    while(wait(NULL) > 0);

}
memset(commands, 0, sizeof(char*) * 100 * 100); //зачем
}


int handle_builtin(char* commands[100][100]){

    if(!strcmp(commands[0][0], "exit")) {
        printf("exit called\n");
        exit(0);
    }

    if(!strcmp(commands[0][0],"cd")){
            if(commands[0][1] == NULL) {
                printf("No arguments were provided for 'cd'\n");
            }
            else if(chdir(commands[0][1])) perror("chdir failed"); //меняет текущую директорию процесса
            return 1;
    }
    
    return 0;
}