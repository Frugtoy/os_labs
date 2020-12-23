#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#define child_proc 0
#define buff_size 32

time_t timer;
void out();
void print_received_data(char * buff);
void err(int err_code);

int main() {
    const char * path = "shm";
    int status;
    char* shmat_status;


    key_t key = ftok(path,'`');
    /*key_t ftok(char *pathname, char proj_id);

       Today,  proj_id is an int, but still only 8 bits are used.  Typical usage has
       an ASCII character proj_id, that is why the behavior is said to be  undefined
       when proj_id is zero.

       Of  course,  no  guarantee  can  be given that the resulting key_t is unique.
       Typically, a best-effort attempt combines the given proj_id byte,  the  lower
       16 bits of the inode number, and the lower 8 bits of the device number into a
       32-bit result.  Collisions may easily happen, for example  between  files  on
       /dev/hda1 and files on /dev/sda1.
*/

    status = shmget(key, buff_size, IPC_EXCL);
    status == -1 ? err(-2) : "ok"; 

    shmat_status = shmat(status,NULL,0);
    
    shmat_status == ((char*)-1) ? err(-3) : print_received_data(shmat_status) ;
   

    
    
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
        default:
            break;
    }
    exit(err_code);
}

void print_received_data(char *buff){

    
    for(;;){
        strcmp(buff,"DEAD") == 0 ?  out() : "ok";
        timer = time(NULL);
        printf("[%x] %s\n %s\n", getpid(), ctime(&timer),buff);
        sleep(5);
    }
}