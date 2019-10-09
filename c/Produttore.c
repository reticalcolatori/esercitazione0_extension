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

    char riga[MAX_STRING_LENGTH];
    
    char *tokenPointer;
    char delimiter[] = ":";

    int fd[argc-1];

    if(argc <= 1){
        perror("Invocazione: produttore fileName1.txt fileName2.txt ... fileNameN.txt");
        exit(INV_ERR);
    }

    for(int i = 0; i < argc - 1; i++) {
        fd[i] = open(argv[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0640);
        if(fd[i] < 0){
            perror("P0: Impossibile creare/aprire il file");
            exit(OPEN_ERR);
        }
    }

    while(gets(riga) != NULL){
        strcat(riga, "\n");
        //printf("%s", riga);
        //char *position_ptr = strchr(riga, ':');

        //|
        //1:Toruca\n\0

        tokenPointer = strtok(riga, delimiter);

        if(tokenPointer == NULL){
            perror("Riga malformata!");
            exit(EXIT_FAILURE);
        }
    
        //Ricavo il file descriptor desiderato.
        int nFileDescriptor = atoi(tokenPointer) - 1; //n del file nel quale voglio salvare la riga

        //Controllo che il file su cui deve essere passata la riga sia stato passato.
        if(nFileDescriptor > argc - 1){
            perror("Non è possibile salvare la riga nel file poichè non passato come parametro!");
            exit(EXIT_FAILURE);
        }

        //  |
        //1:Toruca\n\0
        tokenPointer = strtok(NULL, delimiter);        

        //Devo scrivere solo la riga senza il segnalatore di file:
        //Scrivo dalla posizione dopo i ':'
        //Fino alla lunghezza della riga - l'header.
        int nWr = write(fd[nFileDescriptor], tokenPointer, strlen(tokenPointer));

        if(nWr < 0){
            perror("Errore scrittura linea nel file!");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < argc - 1; i++) {
        close(fd[i]);
    }

    return 0;
}