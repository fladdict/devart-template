//
//  FloorSystemRangeSensor.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#pragma once

#ifndef __TheGiantMap__FloorSystemRangeSensor__
#define __TheGiantMap__FloorSystemRangeSensor__

#include "ofMain.h"
#include "FloorSystemInterface.h"
#include "ofxRangeSensorManager.h"
#include <iostream>

class FloorSystemRangeSensor : public FloorSystemInterface{
public:
    FloorSystemRangeSensor();
    virtual void setup(string portName, int speed);
    virtual void update();
    virtual void draw();
    ofxRangeSensorManager sensorManager;
};


#endif /* defined(__TheGiantMap__FloorSystemRangeSensor__) */
