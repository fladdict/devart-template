#include "testApp.h"
#include "ofxGLDParticleBase2D.h"
#include "ofxGLDParticleEmitterBase.h"

ofxGLDParticleBase2D particle;
ofxGLDParticleEmitterBase emitter;

//--------------------------------------------------------------
void testApp::setup(){
    emitter.lifeSpan = 20;
    emitter.lifeSpanVariance = 20;
}

//--------------------------------------------------------------
void testApp::update(){
    emitter.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    emitter.draw();
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
    emitter.addParticles(x, y, 100);
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
