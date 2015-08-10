/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cz.muni.fi.crocs.EduHoc.uploadTool;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author LukeMcNemee
 */
public class MakeThread implements Runnable {

    private String projectPath;
    private int mode = 0;
    private String mote;

    private boolean silent = false;
    private boolean verbose = false;

    public void setVerbose() {
        verbose = true;
    }

    public void setSilent() {
        silent = true;
    }

    public MakeThread(String projectPath, String mote) {
        this.projectPath = projectPath;
        this.mote = mote;
    }

    public MakeThread(String projectPath) {
        this.projectPath = projectPath;
        this.mote = "";
    }

    /**
     * set mode of make
     *
     * @param mode mode 0 for make mode 1 for make upload mode 2 for make clean
     * default mode is 0
     */
    public void select(int mode) {
        this.mode = mode;
    }

    @Override
    public void run() {
        try {
            ExecuteShellCommand com = new ExecuteShellCommand();
            FileWriter writer = new FileWriter();
            if (silent) {
                com.setSilent();
                writer.setSilent();
            }
            if (verbose) {
                com.setVerbose();
                writer.setVerbose();
            }

            writer.appendToFile("#./bin/bash");
            writer.appendToFile("cd " + projectPath);
            switch (mode) {
                case 0:
                    writer.appendToFile("make");
                    if (verbose) {
                        System.out.println("Calling make on target " + projectPath);
                    }
                    break;
                case 1:
                    writer.appendToFile("make upload MONITOR_PORT=" + mote);
                    if (verbose) {
                        System.out.println("Calling make upload on target " + projectPath);
                    }
                    break;
                case 2:
                    writer.appendToFile("make clean");
                    if (verbose) {
                        System.out.println("Calling make clean on target " + projectPath);
                    }
                    break;
                default:
                    writer.appendToFile("make");
                    if (verbose) {
                        System.out.println("Calling make on target " + projectPath);
                    }
                    break;
            }

            //writer.appendToFile("ls");
            writer.close();
            com.executeCommand("chmod a+x " + writer.getFilename());
            com.executeCommand("./" + writer.getFilename());
            if (verbose) {
                com.executeCommand("echo \"shell finished\"");
            }
        } catch (IOException ex) {
            if (!silent) {
                System.err.println("Make thread failed" + ex.toString());
            }
        }
    }

}