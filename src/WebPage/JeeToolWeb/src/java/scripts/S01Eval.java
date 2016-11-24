/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package scripts;

import configuration.Evaluator;
import cz.muni.fi.crocs.EduHoc.Serial.Generator;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author lukemcnemee
 */
public class S01Eval implements Evaluator {

    private final HashSet<String> messages;
    private final File submitedFile;
    private Generator g;

    public S01Eval(HashSet<String> messages, File submitedFile) {
        this.messages = messages;
        this.submitedFile = submitedFile;
    }

    public double count(String seed) {
        g = new Generator(seed);
        Map<Long, String> msgIdRndValues = new HashMap<>();        
        
        long msgCount = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(submitedFile))) {
            String line = br.readLine();
            String[] split = line.split("#");
            Long msgIdNumber = (long) 0;
            try {
                msgIdNumber = Long.parseLong(split[0]);
            } catch (NumberFormatException ex) {
                System.err.println("number parse error");
            }
            if(msgIdRndValues.containsKey(msgIdNumber)){
                if(messages.contains(split[2]) && (split[0]+"#"+split[1]).equals(msgIdRndValues.get(msgIdNumber))){                
                    msgCount++;
                }
            } else {
                while(!msgIdRndValues.containsKey(msgIdNumber)){
                    msgIdRndValues.put((long) msgIdRndValues.size()+1, g.getNextValue());
                }
                if(messages.contains(split[2]) && (split[0]+"#"+split[1]).equals(msgIdRndValues.get(msgIdNumber))){                
                    msgCount++;
                }
            }
            

        } catch (IOException ex) {

        }

        return msgCount/(double) messages.size();
    }

}
