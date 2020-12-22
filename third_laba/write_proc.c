#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define buff_size 32

time_t timer;

void out(int ping);
void send_data(char * buf);
void err(int err_code);


int main(){
    const char * path = "shm";
    int status;
    char* shmat_status;
    signal(SIGINT,out);
    key_t key = ftok(path,'`');
    status = (shmget(key, buff_size, IPC_CREAT| 0666));
    shmat_status = shmat(status,NULL,0);
    
    shmat_status == ((char*)-1) ? err(-3):"ok";
    status == -1 ? err(-2):"ok"; 
    (strlen(shmat_status)) != 0 ?  err(-1) : send_data(shmat_status);
return 0;
}


void out (int ping){
    printf("i'm out\n");
    struct shmid_ds *buf = 0;
    shmctl(ping, IPC_RMID, buf);
    exit(0);
}

void err(int err_code) {
    switch(err_code) {
        case -1:
            printf("process is already sending itself");
            break;
        case -2:
            printf("shared memory error");
            break;
        case -3:
            printf("SHMAT ERROR");
            break;
        default:
            break;
    }
    
    exit(err_code);
}

void send_data(char * buf){

    for(;;){
        timer = time(NULL);
       
        sprintf(buf,"[%x] %s", getpid(), ctime(&timer));
        
    }

}


