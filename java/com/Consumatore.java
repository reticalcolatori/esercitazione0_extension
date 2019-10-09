package com;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class Consumatore {

    public static void main(String[] args) {

        //Controllo argomenti
        if(args.length < 2){
            System.err.println("Invocazione: consumatore  prefix fileName1.txt ... fileNameN.txt");
            System.exit(1);
        }

        FiglioConsumatore[] figli = new FiglioConsumatore[args.length];
        String prefisso = args[0];

        try {
            for(int i = 1; i < args.length ; i++){
                //Devo aprire il file in ingresso.
                File fileIn = new File(args[i]);
                FileReader fileReader = new FileReader(fileIn);

                figli[i] = new FiglioConsumatore(fileIn, fileReader, prefisso);
                Thread thread = new Thread(figli[i]);
                thread.start();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(2);
        }

    }

}