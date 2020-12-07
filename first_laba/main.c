#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define child_proc 0

//funk list
void get_exit_pid_ppid(){printf("\natexit has been started\n An id of the process (PID): %x\n An id of the parent process (PPID): %x\n", getpid(),getppid());}

void fork_inf(pid_t pid){



    switch(pid){
        case -1: 
            printf("it's seems we have a problem with fork on child process");
            break;

        case 0:
            printf("getting an information from child brunch\n");
            sleep(5);
            pid_t c_pid = getpid();
            pid_t c_ppid = getppid();
            printf("    PID: %x\n   PPID: %x\n\n", c_pid, c_ppid);
            break;

        default:
            printf("getting an information from parent brunch:\n   PID:%x\n   CPID:%x\n\n",getpid(),pid);

            int end_of_c_p = waitpid(pid,child_proc,0);
            printf(" child proc with PID (%x) is dead\n", end_of_c_p);
            break;
    }
}

int main(){
    int conclusion = atexit(get_exit_pid_ppid);
    if(conclusion){ printf("error"); }

    pid_t pid =fork();
    fork_inf(pid);
    return 0;
}