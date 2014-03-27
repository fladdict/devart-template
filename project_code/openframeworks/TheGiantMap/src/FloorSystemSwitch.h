//
//  FloorSystemSwitch.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#pragma once

#ifndef __TheGiantMap__FloorSystemSwitch__
#define __TheGiantMap__FloorSystemSwitch__

#include "ofMain.h"
#include "FloorSystemInterface.h"
#include <iostream>

class FloorSystemSwitch : public FloorSystemInterface{
    public:
        FloorSystemSwitch();
        virtual void setup(string portName, int speed);
        
        virtual void update();
    
        string ofxTrimStringRight(string str);
        string ofxTrimStringLeft(string str);
        string ofxTrimString(string str);
        string ofxGetSerialString(ofSerial &serial, char until);
        ofSerial serial;
    
        bool isUpdated;
        std::vector<string> switches;
        int touches[16];
};

#endif /* defined(__TheGiantMap__FloorSystemSwitch__) */
