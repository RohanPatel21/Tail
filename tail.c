#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


char buffer[1];

char buffer_output[1024];

void tail(char *filename, int last_n){

    
    int n = 0;
    int count_line = 0;

    int fd = open(filename, 0);

    while((n = read(fd, buffer, sizeof(buffer))) > 0){

        if(buffer[0] == '\n'){
            count_line++;
        }
    }

    int lines_to_start = 0;

    if(last_n > count_line){
        lines_to_start = 0; 
    }
    else{
        lines_to_start = count_line - last_n;
    }
    

    count_line = 0;

    fd = open(filename, 0);

    while((n = read(fd, buffer, sizeof(buffer))) > 0){

        if(count_line >= lines_to_start){
            for (int i = 0; i<sizeof(buffer); i++) 
            {
                printf("%c",buffer[i]);
            }
        }

        if(buffer[0] == '\n'){
            count_line++;
        }
    }
    
    close(fd);



    // printf("No. of line: %d", count_line);

}

int main(int argc, char* argv[]){
    
    int last_n = 10;
    int fd = 0;
    if(argc == 3){
        if (argv[1][0] == '-'){
            argv[1]++;
            last_n = atoi(argv[1]++);
        }

        

        if((fd = open(argv[2], 0)) < 0){
            printf("File not found");
            exit(1);
        }

        tail(argv[2], last_n);

    }

    if (argc == 2){
        
        if((fd = open(argv[1], 0)) < 0){
            printf("File not found");
            exit(1);
        }

        tail(argv[1], last_n);

    }


}
