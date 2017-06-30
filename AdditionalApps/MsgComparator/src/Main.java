
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author lukemcnemee
 */
public class Main {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
        percentages();
        diff();
        /*
         File results = new File("results.txt");
         BufferedWriter bw = new BufferedWriter(new FileWriter(results));
         bw.write("file:");
         for (File fileEntry2 : folder.listFiles()) {
         bw.write(fileEntry2.getName() + ":");
         bw.write(fileEntry2.getName() + " pos:");
         bw.write(fileEntry2.getName() + " neg:");
         }
         bw.write("\n");
         for (File fileEntry : folder.listFiles()) {
         src = new SourceMessagesFile();
         src.readFile(fileEntry.getAbsolutePath());
         bw.write(fileEntry.getName() + ":");
         challenge = new ChallengeMsgFile(src);
         for (File fileEntry2 : folder.listFiles()) {

         challenge.readFile(fileEntry2.getName());
         bw.write(challenge.processFile() + ":");
         bw.write(challenge.getCountPos() + ":");
         bw.write(challenge.getCountNeg() + ":");
         }
         bw.write("\n");
         }
         bw.flush();
         bw.close();
         */
    }

    public static void percentages() {
        SourceMessagesFile src = new SourceMessagesFile();
        //all possible messages
        String srcFile = "messages3.txt";
        src.readFile(srcFile);

        ChallengeMsgFile challenge = new ChallengeMsgFile(src);

        //dir with solutions
        File folder = new File("./files_2017");
        System.out.println(folder.exists());
        for (File fileEntry : folder.listFiles()) {
            challenge.readFile(fileEntry.getAbsolutePath());
            System.out.println(fileEntry.getName() + ": score :" + (Math.round(challenge.processFile()*1000))/(double)1000 + 
                    ": msgs : " + challenge.getCountPos() + ": duplicates :" + challenge.getMultiple() );

        }
    }

    public static void diff() throws IOException {
        File folder = new File("./files_2017");
        System.out.println(folder.exists());

        File results = new File("results.txt");
        BufferedWriter bw = new BufferedWriter(new FileWriter(results));
        bw.write("file:");
        for (File fileEntry : folder.listFiles()) {
            bw.write(fileEntry.getName() + ":");
            bw.write(fileEntry.getName() + " pos:");
            bw.write(fileEntry.getName() + " neg:");
        }
        bw.write("\n");
        for (File fileEntry : folder.listFiles()) {
            SourceMessagesFile src = new SourceMessagesFile();
            src.readFile(fileEntry.getAbsolutePath());
            bw.write(fileEntry.getName() + ":");
            for (File fileEntry2 : folder.listFiles()) {
                ChallengeMsgFile challenge = new ChallengeMsgFile(src);
                challenge.readFile(fileEntry2.getAbsolutePath());
                //System.out.println("msgs count" + src.getNumMsgs());
                //System.out.println(fileEntry + " vs " + fileEntry2 + " score " + challenge.processFile());
                bw.write(challenge.processFile() + ":");
                bw.write(challenge.getCountPos() + ":");
                bw.write(challenge.getCountNeg() + ":");
                
            }
            bw.write("\n");
        }

        bw.flush();
        bw.close();
    }
}
