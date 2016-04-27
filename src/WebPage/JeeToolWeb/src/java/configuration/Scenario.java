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
public interface Scenario {
    
    public void run();
    
    public Map<Integer, Integer> getNodesMessageCount();
    
    public boolean verifyPresentNodes();
    
}
