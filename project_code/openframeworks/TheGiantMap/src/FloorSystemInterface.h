//
//  FloorSystemInterface.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#pragma once

#ifndef __TheGiantMap__FloorSystemInterface__
#define __TheGiantMap__FloorSystemInterface__

#include "ofMain.h"
#include <iostream>

class FloorSystemInterface{
    public:
        FloorSystemInterface();
        virtual void setup();
        virtual void tearDown();
        virtual void update();
        virtual void draw();
        void notifyEvent(float x, float y);
    
        ofEvent<ofVec2f> floorTouched;
};

#endif /* defined(__TheGiantMap__FloorSystemInterface__) */
