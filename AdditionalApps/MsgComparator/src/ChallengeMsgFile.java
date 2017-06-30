
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author lukemcnemee
 */
public class ChallengeMsgFile {

    private List<String> msgs = new ArrayList();
    private Set<String> logged = new LinkedHashSet();
    private File sourceFile;
    private SourceMessagesFile src;
    private int countPos = 0;
    private int countNeg = 0;
    private int multiple = 0;

    public int getMultiple() {
        return multiple;
    }

    public ChallengeMsgFile(SourceMessagesFile src) {
        this.src = src;
    }

    public void readFile(String filename) {
        msgs.clear();
        logged.clear();
        sourceFile = new File(filename);
        try (BufferedReader br = new BufferedReader(new FileReader(sourceFile))) {
            String line = br.readLine();
            while (line != null) {
                msgs.add(line);
                line = br.readLine();
            }
        } catch (IOException ex) {

        }
    }

    public int getCountPos() {
        return countPos;
    }

    public int getCountNeg() {
        return countNeg;
    }

    public double processFile() {
        countNeg = 0;
        countPos = 0;
        multiple = 0;
        Iterator<String> i = msgs.iterator();
        while (i.hasNext()) {
            String s = i.next();
            String s2 = src.compareMsg(s);
            if (s2 != null) {
                if(logged.contains(s2)){
                    multiple++;
                } else {
                    
                    logged.add(s2);
                    countPos++;
                }
                
            } else {
                countNeg++;
            }
        }
        if (countNeg > 0) {
            //System.out.println(sourceFile.getName() + " Count neg is nonzero: " + countNeg);
        }
        if (multiple > 0) {
            //System.out.println(sourceFile.getName() + " Count multiple is nonzero: " + multiple);
        }

        return countPos / (double)src.getNumMsgs();
    }
}
