//
//  ofxGLDSpringManager.cpp
//  ofxGLDSpring
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#include "ofxGLDSpringManager.h"

ofxGLDSpringManager::ofxGLDSpringManager(){
    
}


void ofxGLDSpringManager::update(){
    updateForce();
    updateNodes();
    resetForce();
}


void ofxGLDSpringManager::updateForce(){
    
}


void ofxGLDSpringManager::updateNodes(){
    
}

void ofxGLDSpringManager::resetForce(){
    
}


void ofxGLDSpringManager::draw(){
    
}

void ofxGLDSpringManager::addNode(ofxGLDSpringNode &node){
    nodes.push_back(node);
}


void ofxGLDSpringManager::removeNode(ofxGLDSpringNode &node){
    ofxGLDSpringNode nd;
    nodes.remove(nd);
}

/*



*/

/*
void ofxGLDSpringManager::addSpring(ofxGLDSpring &spring){
    //springs.push_back(spring);
}


void ofxGLDSpringManager::removeSpring(ofxGLDSpring &spring)
{
    //springs.remove(spring);
}*/