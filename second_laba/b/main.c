#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>
#define child_proc 0
#define buff_size 128
void write_string( const char * path);
void read_string(const char * path);

time_t timer;
int main() {
   
    int inf = mkfifo("file",0777);
    if(inf == -1){
        printf("there is a problem with creating the fifo");
        exit(-1);
    }
    pid_t pid;
    pid = fork();
    if(pid == child_proc){//child
        read_string("file");
    }
    else {//parent
        
        write_string("file");
        int end_of_c_p = waitpid(pid,child_proc,0);
    }
    system("rm -rf file");
return 0;
}

void write_string( const char * path) {//f[1](parent) writing str to f[0] (child)
  
    char data[buff_size];
    int fd = open(path,O_WRONLY);
    timer = time(0);
    pid_t pid = getpid();
    printf("[%x] *writing my pid and data to child to child*\n",pid);
    sprintf(data,"%s  %x \n",ctime(&timer),pid);
    write(fd, data,buff_size);
    close(fd);
}

void read_string(const char * path){//f[0] (child) reading str from f[1]
    
    char data[buff_size];
    int fd = open(path,O_RDONLY); 
    read(fd, data, buff_size);
    close(fd);
    sleep(5);
    timer = time(0);//time of the proc
    printf( "\n[%x][%s] ",getpid(),ctime(&timer));
    printf("string from parrent: %s",data);
    
}
/*
int mknod(char *path, int mode, int dev);
Параметр dev является несущественным
будем всегда задавать его равным 0
• Параметр path является указателем на строку, содержащую
полное или относительное имя файла, который будет являться
меткой FIFO на диске. Для успешного создания FIFO файла с
таким именем перед вызовом функции не должно существовать.
Параметр mode устанавливает атрибуты прав доступа различных
категорий
пользователей
При создании FIFO реально устанавливаемые права доступа
получаются из стандартной комбинации параметра mode и маски
создания файлов текущего процесса umask, а именно – они равны
(0777 & mode) & ~umask.

int mkfifo(char *path, int mode);

• Параметр mode соответствует параметру mode системного
вызова mknode().
Указатель устанавливается в начале файла. 
это флаги O_RDONLY, O_WRONLY или O_RDWR,
открывающие файлы "только для чтения", "только для записи"
 и для чтения и записи соответственно, которые собрираются с помощью побитовой операции OR из таких значениq/ 
https://www.opennet.ru/man.shtml?topic=open&category=2
*/