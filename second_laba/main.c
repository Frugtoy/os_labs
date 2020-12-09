#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#include<time.h>

#define child_proc 0
#define buff_size 15

void write_string(const char* string , int *fd);
char* read_string(int *fd);


void write_string(const char* string , int *fd) {//f[1] writing str to f[0] (child)
    struct tm *ptr;
    time_t lt;
    lt = time(NULL);
    ptr = localtime(&lt);
    close(fd[0]);
    write(fd[1],string,buff_size);
    close(fd[1]);
    printf("[%x]: ",getpid());
    printf("[%d:%d:%d] *writing str to child*\n",ptr->tm_hour, ptr->tm_min, ptr->tm_sec);

}
char* read_string(int *fd){//f[0] (child) reading str from f[1]
    char *str = (char*)malloc(buff_size + 1);
    struct tm *ptr;
    time_t lt;
    lt = time(NULL);
    ptr = localtime(&lt);
    
    close(fd[1]);
    read(fd[0],str,buff_size);
    close(fd[0]);
    printf("[%x]: ",getpid());
    printf("[%d:%d:%d]: message:",ptr->tm_hour, ptr->tm_min, ptr->tm_sec);

return str;
}

int main(){
    int proc[2];
    pid_t pid;
    

    pipe(proc);
    pid = fork();

    if(pid == child_proc){
        
        write_string("second laba a)",proc);
    }
    else {
        sleep(5);
        char* str = read_string(proc);
        printf(" %s\n",str);
    int end_of_c_p = waitpid(pid,child_proc,0);
 }

    return 0;
}