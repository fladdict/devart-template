//
//  Cloud.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#pragma once

#ifndef __TheGiantMap__Cloud__
#define __TheGiantMap__Cloud__

#include "ofMain.h"
#include <iostream>

class Cloud{
public:
    Cloud();
    void setup();
    void update();
    void resetPosition();
    void draw();
    void addPositionOffset(float x, float y);
    
    float repositionDist;
    float rotation;
    float alpha;
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f scale;
    int wait;
    ofImage images[3];
    int textureIndex;
};

#endif /* defined(__TheGiantMap__Cloud__) */
