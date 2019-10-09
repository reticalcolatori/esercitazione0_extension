package com;

import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Produttore{



    public static void main(String[] args) {
        String delim = ":";

        //Controllo argomenti
        if(args.length <= 1){
            System.out.println("Invocazione: produttore fileName1.txt fileName2.txt ... fileNameN.txt");
            System.exit(1);
        }

        FileWriter[] files = new FileWriter[args.length];

        try {
            for(int i = 0; i < args.length; i++){
                //Devo aprire il file in output.
                files[i] = new FileWriter(args[i]);
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(2);
        }

//        Scanner scanIn = new Scanner(System.in);
//        scanIn.useDelimiter(":");

        BufferedInputStream buffIn = new BufferedInputStream(System.in);
        InputStreamReader rd = new InputStreamReader(buffIn);
        BufferedReader reader = new BufferedReader(rd);

        try{
            String nextLine;


            //Finché l'utente mi passa una riga:
            //Formato 1:blablabla

            while((nextLine = reader.readLine()) != null){
                StringTokenizer token = new StringTokenizer(nextLine, delim);

                //Faccio il parsing della stringa. In caso di errore eccezione.
                int numeroFile = Integer.parseInt(token.nextToken())-1;
                String toWrite = token.nextToken();

                //Controllo file dentro.
                if(args.length <= numeroFile){
                    System.err.println("Non è possibile salvare la riga nel file poichè non passato come parametro!");
                    System.exit(5);
                }

                files[numeroFile].write(toWrite+"\n");
            }

            //Chiudo
            reader.close();

        } catch (IOException e) {
            e.printStackTrace();
            System.exit(3);
        }


        try{
            //Chiudo i files
            for(int i = 0; i < args.length; i++){
                //Devo aprire il file in output.
                files[i].close();
            }
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(4);
        }


    }

}