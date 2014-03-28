/*************************************************************
 URG Range sensor
 
 http://urgnetwork.sourceforge.net/html_ja/urg__sensor_8h.html
 http://urgnetwork.sourceforge.net/html_ja/urg__utils_8h.html#a5a61b1cf3a605381adf533f33905e427
 
**************************************************************/



#include "testApp.h"
#include "ofxRangeSensorManager.h"
#include "ofxRangeSensor.h"



ofxRangeSensorManager sensorManager;
ofxRangeSensor sensor0;
ofxRangeSensor sensor1;

//--------------------------------------------------------------
void testApp::setup(){
    
    //Sensor Grid
    ofxRangeSensorGrid sensorGrid;
    sensorGrid.x = 0;
    sensorGrid.y = 0;
    sensorGrid.width = 2;
    sensorGrid.height = 2;
    sensorGrid.nodeNumX = 51;
    sensorGrid.nodeNumY = 51;
    
    char connect_address[] = "192.168.0.10";
    sensor0.setup(connect_address, 10940);
    sensor0.position.x = -0.1;
    sensor0.position.y = -0.1;
    sensor0.rotation = 45;
    sensor0.scanAngle = 270;
    sensor0.open();

    
    sensor1.position.x = 5.5;
    sensor1.position.y = 5.5;
    sensor1.rotation = 0;//225;
    sensor1.scanAngle = 270;
    
    sensorManager.setup(sensorGrid);
    sensorManager.addSensor(sensor0);
    //sensorManager.addSensor(sensor1);
}

void testApp::exit(){
    sensor0.stop();
    sensor0.close();
}

//--------------------------------------------------------------
void testApp::update(){
    sensorManager.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    
    ofPushMatrix();
        ofTranslate(100, 100);
        ofScale(200, 200);
        sensorManager.draw();
    ofPopMatrix();
    
    ofSetColor(255,255,255,255);
    sensorManager.grayImage.draw(500, 0);
    sensorManager.contourFinder.draw(600, 0);
    
    
    ofPushMatrix();
    ofTranslate(100, 100);
    ofScale(10, 10);
    vector<ofxRangeSensorBlob>::iterator it = sensorManager.blobs.begin();
    while(it != sensorManager.blobs.end()){
        ofSetColor(it->color.r, it->color.g, it->color.b);
        //cout << it->position.x << " " << it->position.y << endl;
        ofEllipse(it->position.x, it->position.y, 5, 5);
        it++;
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    //ofVec2f grid = sensorManager.convertPositionToGridNode(ofVec2f(x/100.0,y/100));
    //cout << grid.x << " " << grid.y << endl;
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
