#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define child_proc 0

char* line = {"________________________________________________________"};

//funk list
void get_exit_pid_ppid(){printf("\n\natexit has been started\n An id of the process (PID): %x\n An id of the parent process (PPID): %x\n%s\n",getpid(),getppid(), line);}

void fork_inf(pid_t pid){



    switch(pid){
        case -1: 
            printf("it's seems we have a problem with fork on child process\n%s\n", line);
            break;

        case 0:
            printf("getting an information from child brunch\n");
            pid_t c_pid = getpid();
            pid_t c_ppid = getppid();
            printf("    PID: %x\n   PPID: %x\n%s\n", c_pid, c_ppid,line);
            break;

        default:
            printf("\n\ngetting an information from parent brunch:\n   PID:%x\n   CPID:%x\n%s\n",getpid(),pid, line);

            int end_of_c_p = waitpid(pid,child_proc,0);
            printf("\n\ninformation from brunch with PID(%x):proc with PID (%x) is dead\n%s\n",getpid(), end_of_c_p ,line);
            break;
    }
}

int main(){
    int conclusion = atexit(get_exit_pid_ppid);
    if(conclusion){ printf("error"); }

    pid_t pid =fork();//fork
    fork_inf(pid);
    printf("\nInformation from brunch with PID(%x)",getpid());
    return 0;
}