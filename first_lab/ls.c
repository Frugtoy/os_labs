#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<grp.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h> 
#include <string.h>
#include<stdbool.h>

#define OUTPUT_BUFFSIZE 120
#define LAST_SECTION 7


int drwxrwxrwx(mode_t chmode, char *buff) {
    int digital_eqv = 0;
    const char permission[] = "drwxrwxrwx";
    for(size_t i = 0; i < 10; i++) {
        buff[i] = (chmode & (1 << (9 - i))) ? permission[i] : '-';
    }
    buff[10] = '\0';
    if(buff[7] == 'r') digital_eqv+=4;
    if(buff[8] == 'w') digital_eqv+=2;
    if(buff[9] == 'x') digital_eqv+=1;
    return digital_eqv;
}
void print(struct dirent *ds) {
    
    struct stat file_info;
    char data_buff[OUTPUT_BUFFSIZE];
    char buff[OUTPUT_BUFFSIZE];
    struct passwd *pwd;
    struct group *file_group;
    off_t is_dir = 0;
  

    
     
    
    stat(ds->d_name, &file_info);
    strftime(data_buff,OUTPUT_BUFFSIZE,"%c",localtime(&file_info.st_mtime));
    int ch_digit = drwxrwxrwx(file_info.st_mode, buff);
    pwd = getpwuid(file_info.st_uid);
    file_group = getgrgid(file_info.st_gid);
    if(ds->d_type == DT_DIR)
        buff[0] = 'd';
        //printf("ok\n");
    printf("%s ",buff);
    
    printf("%i %s %s %s %ld %s\n",
        ch_digit,
        pwd->pw_name, 
        file_group->gr_name, 
        data_buff,
        (long)file_info.st_size,
        ds->d_name);
}

int main( int argc, char *argv[]) {
    int opt;
    bool a_flag = false;
    bool l_flag = false;

    while ((opt = getopt(argc,argv,":al"))  != -1) {

        
        switch (opt)
        {
        case 'l':
            l_flag = true;
            break;
        case 'a':
            a_flag = true;
        default:
            break;
        }
    }
    


    DIR *dir_ptr;
    struct dirent *ds;
    dir_ptr = opendir("./");
    while((ds = readdir(dir_ptr)) != 0) {
        
        if(a_flag && l_flag) print(ds);
        else if(a_flag && !l_flag) printf("%s\n", ds->d_name);
        else if(!a_flag && l_flag && ds->d_name[0] != '.') print(ds);
        else if(ds->d_name[0] != '.') printf("%s\n", ds->d_name);
    }
    closedir(dir_ptr);
    return 0;
}
