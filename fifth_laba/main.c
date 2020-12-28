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
pthread_mutex_t thread;
int arr[r_count];
int main(){

    printf("[tid][arr]\n");   

    pthread_t pthread_arr[r_count + w_count];
    
    pthread_mutex_init(&thread,NULL);

    for(int i = 0; i < r_count; i++){
         pthread_create(&pthread_arr[i],NULL,  read_thread_arr,NULL);
    }
    pthread_create(&pthread_arr[WRITER_IDX],NULL, write_thread_arr,NULL);

    for( int i = 0; i < r_count + w_count; i ++ ){
        pthread_join(pthread_arr[i], NULL);
    }
    pthread_mutex_destroy(&thread);
    return 0;
}

void * write_thread_arr(void * arg){
    for(;;){
        sleep(get_random_val(2));
        pthread_mutex_lock(&thread);
        counter++;
        printf("counter has been increased to [%d]\n",counter);
        printf("[tid][arr]\n");
        arr[get_random_val(10)] = counter;
        sleep(get_random_val(3));
        pthread_mutex_unlock(&thread);
    }  

    
}


int get_random_val(int dist){
   int res =  (rand() +getpid()) % dist; 
    return res;
}

void *  read_thread_arr(void* arg){
    
    for(;;){
        pthread_mutex_lock(&thread);
        printf("[%02x] [",(unsigned)pthread_self());
        for(int i =0; i<r_count; i++){
            printf(" %d ",arr[i]);
        }
        printf("]\n");
        pthread_mutex_unlock(&thread);
        sleep(get_random_val(3));
    }
}