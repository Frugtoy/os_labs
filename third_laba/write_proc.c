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

void out(char* buf , int smid);
void send_data(char * buf);
void err(int err_code);


int main(int argc, char * argv[]){
    const char * path = "shm";
    int status;
    
    char* shmat_status;

    key_t key = ftok(path,'`');
    key == -1 ? err(-4):"ok";
    status = (shmget(key, buff_size, IPC_CREAT| 0666));
    shmat_status = shmat(status,NULL,0);
    argc > 1 ? (strcmp(argv[1],"-c")==0 ? out(shmat_status,status):"ok"):("ok");
    shmat_status == ((char*)-1) ? err(-3):"ok";
    status == -1 ? err(-2):"ok"; 
    (strlen(shmat_status)) != 0 ?  err(-1) : send_data(shmat_status);
return 0;
}


void out (char* buf, int shmid){
    printf("clean shmid\n");
    sprintf(buf,"DEAD");
    struct shmid_ds *buff = NULL;
    shmctl(shmid, IPC_RMID, buff);
    exit(0);
}

void err(int err_code){
    switch(err_code){
        case -1:
            printf("process is already sending itself");
            break;
        case -2:
            printf("shared memory error");
            break;
        case -3:
            printf("SHMAT ERROR");
            break;
        case -4:
            printf("ftok");
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


