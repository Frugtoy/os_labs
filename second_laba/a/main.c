#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#include<time.h>

#define child_proc 0
#define buff_size 15

void write_string( int *fd);
void read_string(int *fd);
time_t timer;
int main() {
    int proc[2];
    pid_t pid;
    pipe(proc);
    pid = fork();

    if(pid == child_proc){//child
        sleep(5);
        read_string(proc);
    }
    else {//parent
        
        write_string(proc);
        int end_of_c_p = waitpid(pid,child_proc,0);
    }

return 0;
}

void write_string( int *fd) {//f[1](parent) writing str to f[0] (child)
  
    long int data[2];
 
    
    data[0] = time(0); //замеряем
    data[1] = getpid();
    close(fd[0]);
    printf("[%x] *writing my pid and data to child to child*\n",getpid());
    write(fd[1],data,sizeof(long int)*2);
    close(fd[1]);
}

void read_string(int *fd){//f[0] (child) reading str from f[1]
    
    long int data[2];
    close(fd[1]);
    read(fd[0], data, sizeof( long int ) * 2 );
    close(fd[0]);
    timer = time(0);//time of the proc
    printf( "\n[%x][%s] ",getpid(),ctime(&timer));
    timer = data[0];
    printf("string from parrent: %s %lx ",ctime(&timer) , data[1]);
    
}