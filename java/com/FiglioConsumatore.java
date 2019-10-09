package com;

import java.io.*;
import java.nio.file.CopyOption;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class FiglioConsumatore implements Runnable {

    private String filtro;


    //Mi serve uno stream del file.
    private FileReader fileReader;

    private File fileOriginale;

    //File temporaneo.
    private File fileTemp;


    public FiglioConsumatore(File fileOriginale, FileReader fileRead, String filtro) {
        this.fileOriginale = fileOriginale;
        this.fileReader = (fileRead);
        this.filtro = filtro;
        //Commento inutile perchè non mi faceva fare il commit.
    }

    @Override
    public void run() {
        //Lo stream del file ingresso lo ha aperto il papi

        //Creo il file temp.
        fileTemp = new File(Thread.currentThread().getId()+".tmp");

        FileWriter fileWriter = null;

        try {
            fileWriter = new FileWriter(fileTemp);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(12);
        }

        int ch;

        try {
            while ((ch = fileReader.read()) != -1) {
                //Non devo trovare il carattere nel prefisso:
                //cerco nella stringa di filtro: se non lo trovo allora il carattere è valido.
                if(filtro.indexOf(ch) == -1){
                    fileWriter.write(ch);
                }
            }

            //Chiudo gli stream
            fileReader.close();
            fileWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
            System.exit(13);
        }



        //ora devo eliminare il file originale
        //e rinominare il file temporaneo come quello originale.

        Path pathSrc = Path.of(fileTemp.toURI());       //La sorgente è il file temporaneo.
        Path pathDest = Path.of(fileOriginale.toURI()); //La destinazione è il file originale.

        try {
            Files.move(pathSrc, pathDest, StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(14);

        }



    }
}
