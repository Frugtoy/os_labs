#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define r_count 10
#define w_count 1
#define WRITER_IDX 10
void* read_thread_arr( void* arg);
void* write_thread_arr(void* arg);
int get_random_val(int dist);

int  counter = 0;
pthread_rwlock_t rwlocker;
int arr[r_count];
int main(){

    printf("[tid][arr]\n");   

    pthread_t pthread_arr[r_count + w_count];
    
    pthread_rwlock_init(&rwlocker,NULL);

    for(int i = 0; i < r_count; i++){
         pthread_create(&pthread_arr[i],NULL,  read_thread_arr,NULL);
    }
    pthread_create(&pthread_arr[WRITER_IDX],NULL, write_thread_arr,NULL);

    for( int i = 0; i < r_count + w_count; i ++ ){
        pthread_join(pthread_arr[i], NULL);
    }
    pthread_rwlock_destroy(&rwlocker);
    return 0;
}

void * write_thread_arr(void * arg){
    for(;;){
        sleep(get_random_val(2));
        pthread_rwlock_wrlock(&rwlocker);
        counter++;
        printf("counter has been increased to [%d]\n",counter);
        printf("[tid][arr]\n");
        arr[get_random_val(10)] = counter;
        sleep(get_random_val(3));
        pthread_rwlock_unlock(&rwlocker);
    }  

    
}


int get_random_val(int dist){
   int res =  (rand() +getpid()) % dist; 
    return res;
}

void *  read_thread_arr(void* arg){
    
    for(;;){
        pthread_rwlock_rdlock(&rwlocker);
        printf("[%lu] [",pthread_self());
        for(int i =0; i<r_count; i++){
            printf(" %d ",arr[i]);
        }
        printf("]\n");
        fflush(stdout);
      
        pthread_rwlock_unlock(&rwlocker);
          sleep(get_random_val(3));
    }
}