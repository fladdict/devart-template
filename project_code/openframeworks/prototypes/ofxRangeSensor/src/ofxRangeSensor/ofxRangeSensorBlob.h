//
//  ofxRangeSensorLabel.h
//  ofxRangeSensor
//
//  Created by 深津 貴之 on 2014/03/20.
//
//

#ifndef __ofxRangeSensor__ofxRangeSensorBlob__
#define __ofxRangeSensor__ofxRangeSensorBlob__

#include "ofMain.h"
#include <iostream>

class ofxRangeSensorBlob{
    public:
        int label;
        ofVec2f position;
        ofVec2f prevPosition;
        int lifeCount;
        int killCount=0;
        bool hasPairedCVBlob;
        ofColor color;
};

#endif /* defined(__ofxRangeSensor__ofxRangeSensorBlob__) */
