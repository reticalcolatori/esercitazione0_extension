#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INV_ERR 1
#define OPEN_ERR 2
#define WR_ERR 3
#define MAX_STRING_LENGTH 256

int main(int argc, char *argv[]){

    int nFigli = argc - 2;
    int pid[nFigli];

    if(argc == 1){
        perror("Invocazione: consumatore  prefix fileName1.txt ... fileNameN.txt");
        exit(INV_ERR);
    }

    for (int i = 0; i < nFigli; i++) {
        /* code */
    }
    

}