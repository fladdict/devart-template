#include "testApp.h"

ofPlanePrimitive plane;
ofImage sourceImage;
ofImage lookupImage;
ofShader shader;

ofFbo nightFbo;
ofShader nightLightShader;

//--------------------------------------------------------------
void testApp::setup(){
    sourceImage.loadImage("source.jpg");
    lookupImage.loadImage("blueprint.png");
    shader.load("shaders/simpleVertex.vert", "shaders/lookupFilter.frag");
    nightLightShader.load("shaders/simpleVertex.vert", "shaders/nightlight.frag");
    
    nightFbo.allocate(sourceImage.width, sourceImage.height);
    
    
    plane.set(1000, 500, 10, 10);
    plane.mapTexCoords(0, 0, sourceImage.getWidth(), sourceImage.getHeight());
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255,255);
    
    nightFbo.begin();
    shader.begin();
    shader.setUniformTexture("sourceTexture", sourceImage.getTextureReference(), 1);
    shader.setUniformTexture("lookupTexture", lookupImage.getTextureReference(), 2);
    shader.setUniform1f("interpolation", 1.0);
    ofTranslate(sourceImage.width*0.5, sourceImage.height*0.5);
    plane.draw();
    shader.end();
    nightFbo.end();
    
    
    
    
    nightLightShader.begin();
    nightLightShader.setUniform1f("randomSeed", ofRandom(0,100));
    nightLightShader.setUniform1f("lightThreshold", 0.6);
    nightLightShader.setUniform1f("lightAmplifier", 0.1);
    nightFbo.draw(0, 0);
    nightLightShader.end();
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
