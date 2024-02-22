#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGUMENTS 10

void pipe_command(char *input){

    //char input[MAX_INPUT_LENGTH];
       char *arguments[MAX_ARGUMENTS];
    int num_arguments = 0;
        int i,j;
    char *token = strtok(input, "|");
    while (token != NULL) {
        // Add the token to the arguments array
        arguments[num_arguments] = token;
        num_arguments++;

        // If we've reached the maximum number of arguments, exit with an error
        if (num_arguments >= MAX_ARGUMENTS) {
            fprintf(stderr, "Error: too many arguments\n");
            exit(EXIT_FAILURE);
        }

        // Get the next token
        token = strtok(NULL, "|");
    }

    // Create pipes
    int **pipes = malloc(sizeof(int*) * (num_arguments - 1));
    for ( i = 0; i < num_arguments - 1; i++) {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) < 0) {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }

    // Fork processes
    pid_t *pids = malloc(sizeof(pid_t) * num_arguments);
    for ( i = 0; i < num_arguments; i++) {
        if ((pids[i] = fork()) < 0) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            // Child process

            // Redirect input from previous pipe
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }

            // Redirect output to next pipe
            if (i < num_arguments - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            // Close all pipes in child process
            for (j = 0; j < num_arguments - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
// Tokenize the input string based on whitespace characters
            int numargs = 0;
            char **argumentss = malloc(sizeof(char *) * MAX_ARGUMENTS);
            char *token = strtok(arguments[i], " \t\n");
            while (token != NULL) {
                // Add the token to the arguments array
                argumentss[numargs] = token;
                numargs++;

                // If we've reached the maximum number of arguments, exit with an error
                if (numargs >= MAX_ARGUMENTS) {
                    fprintf(stderr, "Error: too many arguments\n");
                    exit(EXIT_FAILURE);
                }

                // Get the next token
                token = strtok(NULL, " \t\n");
            }

            // Execute command
            if (execvp(argumentss[0], argumentss) < 0) {
                perror("exec error");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Close all pipes in parent process
    for ( i = 0; i < num_arguments - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for child processes to finish
    for ( i = 0; i < num_arguments; i++) {
        waitpid(pids[i], NULL, 0);
    }
    // Free allocated memory
for ( i = 0; i < num_arguments - 1; i++) {
free(pipes[i]);
}
free(pipes);
free(pids);

    }


char** split_string(char* str) {
    int len = strlen(str);
    int count = 1;
   int i;
    for ( i = 0; i < len; i++) {
        if (str[i] == ' ') {
            count++;
        }
    }

    char** str_arr = (char**)malloc(count * sizeof(char*));
     if (str_arr == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    char* token = strtok(str, " ");
     i = 0;

    while (token != NULL) {
        str_arr[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    str_arr[i] = NULL;

    return str_arr;
}

void run_command(char **command) {
    int i = 0;
    int in_file = 0, out_file = 0;
    char *input_file = NULL, *output_file = NULL;

 while (command[i] != NULL) {
        if (strcmp(command[i], "<") == 0) {
            /* Input redirection */
            in_file = 1;
            input_file = command[i+1];
            command[i] = NULL;
        } else if (strcmp(command[i], ">") == 0) {
            /* Output redirection */
            out_file = 1;
            output_file = command[i+1];
            command[i] = NULL;
        }
        i++;
    }

    /* Split the command into arguments */
    // token = strtok(command, " ");
    // while (token != NULL && i < 80) {
    //     args[i] = token;
    //     token = strtok(NULL, " ");
    //     i++;
    // }
    // args[i] = NULL;  /* Make sure the argument list is terminated with NULL */

    /* Fork a new process to run the command */
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
return;
    } else if (pid == 0) {
        if (in_file) {
            int fd = open(input_file, O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        /* Redirect output if necessary */
        if (out_file) {
            int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd == -1) {
                perror("open");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        /* Child process */
        execvp(command[0], command);
        perror(command[0]);  /* execvp() only returns if an error occurs */
        exit(1);
    } else {
        /* Parent process */
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                printf("Command exited with status %d\n", exit_status);
            }
        } else if (WIFSIGNALED(status)) {
            int signal_num = WTERMSIG(status);
            printf("Command terminated by signal %d\n", signal_num);
        }
    }
}
    void mycd(char *dir) {
    /* Change the current working directory of the toolkit. */
    if (dir == NULL || strlen(dir) == 0) {
        /* If no argument is provided, change to the home directory. */
        char *home_dir = getenv("HOME");
        if (home_dir != NULL) {
            chdir(home_dir);
        }
    } else {
        /* Change to the specified directory. */
        chdir(dir);
    }
}

void mypwd() {
    /* Print the absolute path of the current working directory. */
    char cwd[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    }
}
void myexit() {
    /* Terminate the toolkit. */
    exit(0);
}

int main() {
    char input[81];
    char *command;
    


    /* Main loop */
    while (1) {
        /* Print the prompt */
        printf("$ ");
        fflush(stdout);

        /* Read the input from the user */
        if (fgets(input, sizeof(input), stdin) == NULL) {
            /* End of file encountered */
            myexit();
        }
           if (strlen(input) == 1) {
            continue;
        }
        /* Remove the newline character */
        input[strcspn(input, "\n")] = '\0';

          if (strchr(input, '|') != NULL) {
        /* Input contains pipes, pass to pipe_command function */
        pipe_command(input);
    }
    else{
        /* Split the input into command and argument */
        char** str_arr = split_string(input);
        command = str_arr[0];
        /* Execute the command */
        if (strcmp(command, "mycd") == 0) {
            //mycd(str_arr);
        } else if (strcmp(command, "mypwd") == 0) {
            mypwd();
        } else if (strcmp(command, "myexit") == 0) {
            myexit();
        } else if(command!=NULL){
            run_command(str_arr);
        }
    }

    }

    return 0;
}
