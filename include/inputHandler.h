/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inputHandler.h
 * Author: tartg
 *
 * Created on 18. Oktober 2016, 10:35
 */

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <GLFW/glfw3.h>
#include <AntTweakBar.h>


/*
 * Simple input Handler 
 */
class inputHandler {
public:

    /**
     * Constructor for input Handling
     */
    inputHandler(GLFWwindow* window);
    
    /**
     * Generate a new anttweak bar
     * @param description - Name of the bar
     * @return referenze to the Bar. Destruction is handled in exit.
     */
    static TwBar* createNewBar(const std::string& name, const std::string& description);
    
    /**
     * update all anttweak bars
     */
    void update();
    
    /**
     * Close input handling
     */
    void exit();
    

private:

    GLFWwindow* window; //reference to the window
    float scorllpos;
};

#endif /* INPUTHANDLER_H */

