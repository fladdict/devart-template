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
#include "ofxOpenCv.h"
#include <iostream>



typedef struct ofxRangeSensorGrid{
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
    
        //Blob Management
        void prepareUpdateBlobs();
        void checkNewBlobs();
        void deleteUnlinkedBlobs();
        ofxRangeSensorBlob getNewBlob();
    
        //Utils
        ofVec2f convertSensorStepToPosition(ofxRangeSensor *sensor, int step);
        ofVec2f convertPositionToGridNode(ofVec2f position);
    
    
        vector<ofxRangeSensor> sensors;
        ofxRangeSensorGrid sensorGrid;
    
        unsigned char *pixels;
        float *data;
        //float data[256][256];
    
        //For OpenCV Recognition
        ofxCvGrayscaleImage grayImage;
        ofxCvContourFinder contourFinder;
        vector<ofxRangeSensorBlob> blobs;
        vector<ofxRangeSensorBlob> unusedBlobs;
};


#endif /* defined(__ofxRangeSensor__ofxRangeSensorManager__) */
