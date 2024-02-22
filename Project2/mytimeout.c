#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_timeout(int signum) {
   
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: mytimeout.x snds cmd [cmd-args]\n");
        exit(1);
    }
    
    int timeout = atoi(argv[1]);
    char *command = argv[2];
    char *args[argc-2];
    int i;
    for (i = 0; i < argc-2; i++) {
        args[i] = argv[i+2];
    }
    args[i] = NULL;
    
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        /* Child process */ 
        alarm(timeout);
         
        execvp(args[0], args);
       
        perror(command);  /* execvp() only returns if an error occurs */
        exit(1);
    } else {
        /* Parent process */
        //signal(SIGALRM, handle_timeout);
        
        int status;
        waitpid(pid, &status, 0);
       
      
    }
    
    return 0;
}
