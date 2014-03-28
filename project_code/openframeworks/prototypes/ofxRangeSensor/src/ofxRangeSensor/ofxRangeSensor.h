//
//  ofxRangeSensor.h
//  ofxRangeSensor
//
//  Created by 深津 貴之 on 2014/02/28.
//
//

#ifndef __ofxRangeSensor__ofxRangeSensor__
#define __ofxRangeSensor__ofxRangeSensor__

#include "ofMain.h"
#include "urg_sensor.h"
#include <iostream>

class ofxRangeSensor{
    public:
        ofxRangeSensor();
        void setup(char address[], long port);
        void update();
        void open();
        void close();
        void start();
        void stop();
    
        float stepToAngle(int step);
        float stepToRadian(int step);
        float stepToGlobalAngle(int step);
        float stepToGlobalRadian(int step);
    
        ofVec2f position;       //metor
        bool enabled = true;
        bool debugMode = false;
    
        //Connection Data
        char connect_address[16];
        long connect_port;
        urg_t urg;
        long *tempData;
        long *data;
        bool isOpen;
        bool isStart;
    
        //URG Params
        long minDistance; //0;
        long maxDistance; //30000;
        int minStep; //minStepNum -540;
        int maxStep; //maxStepNum 540;
        int dataSize;
    
        float rotation = 0;     //0-360 degree
        int scanAngle = 270;    //from -135 degree(1080 step) and 135 degree(0 step).
        float scanStep = 1081;  //Default URG is 1081 steps
        float scanRange = 10;   //Not used
    
        //float data[1081];
};

#endif /* defined(__ofxRangeSensor__ofxRangeSensor__) */
