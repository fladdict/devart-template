#include "testApp.h"

ofShader shader;
ofImage image0;
ofImage image1;

//--------------------------------------------------------------
void testApp::setup(){
    image0.loadImage("texture0.png");
    image1.loadImage("texture1.png");
    shader.load("vert.vert", "frag.frag");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    shader.begin();

    
    //Normal Blending
    ofEnableAlphaBlending();
    ofSetColor(255);
    image0.draw(0,0);
    image1.draw(0,0);
    
    /*******************
     with ofSetColor doesn't work
     *******************/
    image0.draw(256,0);
    ofSetColor(255, 255, 255, 10);
    image1.draw(256,0);
    
    /*******************
     with ofSetColor doesn't work
     *******************/
    
    //ofSetColor(255, 255, 255, 255);
    image0.draw(512,0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255, 255, 255, 10);
    image1.draw(512,0);
    ofDisableBlendMode();
    ofDisableAlphaBlending();
    
    shader.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
