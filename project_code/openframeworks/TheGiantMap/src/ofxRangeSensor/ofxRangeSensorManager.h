//
//  ofxRangeSensorManager.h
//  ofxRangeSensor
//
//  Created by 深津 貴之 on 2014/02/28.
//
//

#pragma once

#ifndef __ofxRangeSensor__ofxRangeSensorManager__
#define __ofxRangeSensor__ofxRangeSensorManager__

#include "ofMain.h"
#include "ofxRangeSensor.h"
#include "ofxRangeSensorBlob.h"
#include <iostream>



struct ofxRangeSensorGrid{
    float x = 0;
    float y = 0;
    float width = 10;
    float height = 10;
    int nodeNumX;
    int nodeNumY;

};

class ofxRangeSensorManager{
    public:
        ofxRangeSensorManager();
        void setup(ofxRangeSensorGrid grid);
        void tearDown();
        void update();
        void updateSensor();
        void updateOpenCv();
        void draw();
        void drawSensor(ofxRangeSensor *sensor);
        void resetGrid();
        void addSensor(ofxRangeSensor sensor);
        void updateGridTile(int x, int y);
    
        //Utils
        ofVec2f convertSensorStepToPosition(ofxRangeSensor *sensor, int step);
        ofVec2f convertPositionToGridNode(ofVec2f position);
    
        vector<ofxRangeSensor> sensors;
        ofxRangeSensorGrid sensorGrid;
        unsigned char *pixels;
};


#endif /* defined(__ofxRangeSensor__ofxRangeSensorManager__) */
