
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedHashSet;
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
public class SourceMessagesFile {
    private Set<String> msgs = new LinkedHashSet();
    private Set<String> msgs2 = new LinkedHashSet();
    private File sourceFile;
    
    public void readFile(String filename){
        msgs.clear();
        msgs2.clear();
        sourceFile = new File(filename);
        try(BufferedReader br = new BufferedReader(new FileReader(sourceFile))){
            String line = br.readLine();
            while(line != null){
                msgs.add(line);
                msgs2.add(line.replaceAll(" ", ""));                
                line = br.readLine();
            }
        } catch (IOException ex){
            System.err.println("error");
        }
        System.out.println("size " + msgs.size());
    }
    
    public int getNumMsgs(){
        return msgs.size();
    }
    
    public String compareMsg(String msg){
        if(!msg.contains("#")){
            return null;
        }
        if(!msg.startsWith("#")){
            msg = msg.substring(msg.indexOf("#"));
        } 
        if(msg.contains("CRC error")){
            return null;
        } 
        if(msg.isEmpty()){
            return null;
        }
        if(msg.contains("[.]")){
            msg = msg.replaceAll("[.]", "");
        }
        if(msgs.contains(msg)){
            return msg;
        }        
        //strip all spaces
        String msgEdit = msg.replaceAll(" ", "");
        if(msgs2.contains(msgEdit)){
            return msgEdit;
        }
        //System.out.println("not found");
        return null;
    }
    
    
}
