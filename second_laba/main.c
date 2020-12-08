#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

#include<time.h>

#define child_proc 0
#define dev 0

void write_string(const char* string , FILE* file);
void read_string (FILE* file);


void write_string(const char* string , FILE*file){
    struct tm *ptr;
    time_t lt;
    lt = time(NULL);
    ptr = localtime(&lt);
    printf("[%x]: ",getpid());
    printf("[%d %d %d]:[put str into the file]\n",ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
    fprintf(file,"%s", string);
    fflush(file);
}
void read_string(FILE* file){
        
        struct tm *ptr;
        time_t lt;
        lt = time(NULL);
        ptr = localtime(&lt);
    
    printf("[%x]: ",getpid());
    printf("[%d %d %d]: message: ",ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
    char buf[256];
    while(!feof(file) && !ferror(file) && fgets(buf,sizeof(buf),file) != NULL)
        fputs(buf,stdout);
}

int main(){
    int proc[2];
    pid_t pid;
    

    pipe(proc);
    pid = fork();
    if(pid == child_proc){
        sleep(5);
        FILE* file;
        
        file = fopen("pipe.txt","r");
        
        read_string(file);
        
        close(proc[0]);
        
    }
    else {
    FILE* file;
    file = fopen("pipe.txt", "w");

    write_string("second laba a)", file);
    
    close(proc[1]);
    int end_of_c_p = waitpid(pid,child_proc,0);
 }

    return 0;
}