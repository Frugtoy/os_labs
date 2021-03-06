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
#include<sys/sem.h>
#include<sys/types.h>

#define buff_size 32
#define nsems 1
#define SEMOPEN {0,1,0}
#define SEMLOCK {0,-1,0}
time_t timer;

enum locker {
    LOCK = 0,
    OPEN = 1
};
struct sembuf sem_status [] ={SEMLOCK,SEMOPEN};
void out();
void print_received_data(char * buff, int semid);
void err(int err_code);

int main(int argc, char * argv[]){
    const char * path = "write_proc.c";
    int status,semoph_status;
    char* shmat_buf;

   key_t key = ftok(path,0X1001001);
   key_t skey = ftok("Makefile",0X1001001);
   skey  == -1 ? err(-4): ( key == -1 ? err(-4) : "ok");
   

    status = shmget(key, buff_size,0666);
    semoph_status = semget(skey,nsems,0666);

    shmat_buf = shmat(status,NULL,0);
    argc > 1 ? (strcmp(argv[1],"-c")==0 ? out(shmat_buf,status):"ok"):("ok");
    shmat_buf == ((char*)-1) ? err(-3):"ok";
    status == -1 ? err(-2):"ok"; 
    
    print_received_data(shmat_buf,semoph_status);
return 0;
}
void out (){
    printf("im' out\n");
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
        case -5:
            printf("SEMOPH ERROR");
        case -6:
            printf("SEMGET ERROR");
        default:
            break;
    }
    exit(err_code);
}

void print_received_data(char *buff, int semid){

    
    for(;;){
        strcmp(buff,"DEAD") == 0 ?  out() : "ok";
        semop(semid,&sem_status[OPEN],1);
        timer = time(NULL);
        printf("[%x] [%s] %s", getpid(), ctime(&timer), buff);
        sleep(1);
        semop(semid,&sem_status[LOCK],1);
    }
}