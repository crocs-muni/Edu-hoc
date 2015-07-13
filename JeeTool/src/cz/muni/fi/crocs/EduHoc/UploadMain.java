/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package cz.muni.fi.crocs.EduHoc;

import static cz.muni.fi.crocs.EduHoc.Main.help;
import cz.muni.fi.crocs.EduHoc.uploadTool.MoteList;
import java.io.File;

/**
 *
 * @author LukeMcNemee
 */
public class UploadMain {
    private MoteList motelist;
    private File makefile;
    private String projectPath;
    
    
    public UploadMain(MoteList motelist, String projectPath) {
        this.motelist = motelist;
        
        this.projectPath = projectPath;
        
        if (projectPath.charAt(projectPath.length() - 1) == '/') {
            makefile = new File(projectPath + "Makefile");
        } else {
            makefile = new File(projectPath + "/Makefile");
        }
        System.out.println("processing makefile for project at " + projectPath);
        if (!makefile.exists()) {
            System.err.println("makefile not found");
            Main.help();
            return;
        }
        System.out.println("Makefile " + makefile.getPath() + " found");
    }
    
    
    public  void StartUpload(){
        
    }
}