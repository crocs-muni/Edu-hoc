/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package configuration;

import cz.muni.fi.crocs.EduHoc.SerialMain;
import cz.muni.fi.crocs.EduHoc.UploadMain;
import cz.muni.fi.crocs.EduHoc.uploadTool.MoteList;
import java.util.Map;

/**
 *
 * @author lukemcnemee
 */
public class S01 implements Scenario {

    public static final String PATH = System.getenv("EDU_HOC_HOME") + "/src/Scenarios/01";
    public static final String WRITE_FILES = System.getenv("EDU_HOC_HOME") + "/AdditionalScripts/";
    private String seed;
    
    public String displayStatus(){
        return "Scenario 1 running";
    }
    
    public String displaySeed(){
        return seed;
    }
    
    @Override
    public void run() {
        //make upload
        MoteList motes = new MoteList(System.getenv("EDU_HOC_HOME") + "/config/motePaths.txt");
        UploadMain upload = new UploadMain(motes, PATH);
        upload.setSilent();
        upload.makeUpload();
        
        //listen + write
        SerialMain serial = new SerialMain(motes, (long) 15);
        serial.connect();
        seed = serial.getG().getHexSeed();
        serial.write(WRITE_FILES, (long) 1);
        //display results
    }

    @Override
    public Map<Integer, Integer> getNodesMessageCount() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean verifyPresentNodes() {
        //detect and count

        return true;
    }

}
