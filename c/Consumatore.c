#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INV_ERR 1
#define OPEN_ERR 2
#define WR_ERR 3
#define FORK_ERR 4
#define EXEC_ERR 5

#define MAX_STRING_LENGTH 256

int main(int argc, char *argv[]){

    int nFigli = argc - 2;
    int pid[nFigli];
    int fd;

    if(argc <= 2){
        perror("Invocazione: consumatore  prefix fileName1.txt ... fileNameN.txt");
        exit(INV_ERR);
    }

    for (int i = 0; i < nFigli; i++) {

        //Controllo esistenza file per il figlio:
        //Apro e verifico.
        fd = open(argv[2+i], O_RDWR);

        if(fd < 0)
        {
            perror("Il file non esiste oppure non è nel direttorio corrente, oppure non posso leggere/scrivere.");
            exit(OPEN_ERR);
        }

        pid[i] = fork();

        if(pid[i] == 0){
            //Figlio

            //Abbiamo già aperto il file da leggere e filtrare: si trova in fd.
            //Ora dobbiamo aprire il temporaneo.

            //Per prima cosa creo il nome del file temporaneo.
            //per esempio 12356.tmp (pid.tmp)

            char fileTmpName[MAX_STRING_LENGTH];
            
            sprintf(fileTmpName, "%d.tmp", getpid());


            int fdTemp = open(fileTmpName, O_RDWR | O_CREAT | O_TRUNC, 0644);

            if(fdTemp < 0)
            {
                perror("Impossibile creare il file temporaneo.");
                exit(OPEN_ERR);
            }

            //ho aperto il file temp.

            //inizio a scrivere nel temp.

            char ch;
            int presente = 0;

            while((read(fd, &ch, sizeof(char))) > 0){
                for(int i = 0; i < strlen(argv[1]) && !presente; i++){
                    if(argv[1][i] == ch) //se non sono presente nella string prefix allora mi stampi altrimenti mi salti
                        presente = 1;
                }

                if(!presente)
                    write(fdTemp, &ch, sizeof(char));
                
                presente = 0;
            }

            //----------------------------------------------

            //Idea alternativa:
            //Ripristino gli I/O Pointer e riscrivo il file originale.
            //Problema: se lunghezza file originale > lunghezza file temp?

            //Ripristino gli i/o pointer
            //lseek(fd, 0, SEEK_SET);
            //lseek(fdTemp, 0, SEEK_SET);

            //Trascrivo il file
            //while((read(fdTemp, &ch, sizeof(char))))...

            //----------------------------------------------

            //Alla fine di lettura/scrittura devo chiudere i file.
            close(fd);
            close(fdTemp);
      
            //Faccio la move.
            execlp("mv", "mv", fileTmpName, argv[2+i], 0);

            perror("Exec fallita");
            exit(EXEC_ERR);

        }else if(pid[i] < 0){
            perror("Fork fallita");
            exit(FORK_ERR);
        }

        //Il padre deve chiudere il file descriptor.
        close(fd);

    }


    //NON Devo aspettare i figli.
    
    return 0;
}