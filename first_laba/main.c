#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#define child_proc 0

char* line = {"________________________________________________________"};

//funk list
void get_exit_pid_ppid(){printf("atexit has been started\n[%x]: An id of the process (PID): %x\n[%x]: An id of the parent process (PPID): %x\n\n",getpid(),getpid(),getpid(),getppid());}

void fork_inf(pid_t pid){



    switch(pid){
        case -1: 
            printf("[%x]: it's seems we have a problem with fork on child process\n\n", getpid());
            break;

        case 0:
            printf("[%x]: getting an information from child brunch\n", getpid());
            pid_t c_pid = getpid();
            pid_t c_ppid = getppid();
            printf("[%x]:  PID: %x\n[%x]: PPID: %x\n\n",getpid(),getpid(), c_pid, c_ppid);
            break;

        default:
            printf("\n\n[%x]: getting an information from parent brunch:\n[%x]: PID:%x\n[%x]: CPID:%x\n\n",getpid(),getpid(),getpid(),getpid(),pid);

            int end_of_c_p = waitpid(pid,child_proc,0);
            printf("\n\n[%x]:process with PID (%x) is dead\n\n",getpid(), end_of_c_p);
            break;
    }
}

int main(){
    int conclusion = atexit(get_exit_pid_ppid);
    if(conclusion){ printf("error"); }

    pid_t pid =fork();//fork
    fork_inf(pid);
    printf("\n[%x]: ",getpid());
    return 0;
}