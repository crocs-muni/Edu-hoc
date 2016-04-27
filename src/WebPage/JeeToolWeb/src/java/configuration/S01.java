/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package configuration;

import java.util.Map;


/**
 *
 * @author lukemcnemee
 */
public  class S01 implements Scenario{

    public static final String PATH = System.getenv("EDU_HOC_HOME") + "/src/Scenarios/01";
    
    
    
    @Override
    public void run() {
        //make upload
        
        //listen + write
        
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
