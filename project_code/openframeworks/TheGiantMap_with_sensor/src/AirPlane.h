//
//  AirPlane.h
//  TheGiantMap_Sketch01
//
//  Created by 深津 貴之 on 2014/02/16.
//
//

#ifndef __TheGiantMap_Sketch01__AirPlane__
#define __TheGiantMap_Sketch01__AirPlane__

#include <iostream>
#include "ofMain.h"

class AirPlane{
public:
    AirPlane();
    void setup();
    void addPositionOffset(float x, float y);
    void explode();
    void resetPosition();
    void update();
    void draw();
    
    float repositionDist;
    ofVec3f position;
    ofVec3f velocity;
    ofImage image;
    ofImage smokeImage;
};


class AirPlaneSmoke
{
public:
    AirPlaneSmoke();
    void setup();
    void update();
    void draw();
    void addPositionOffset(float x, float y);
    int lifeCount;
    ofVec3f position;
    float alpha;
    float scale;
};

#endif /* defined(__TheGiantMap_Sketch01__AirPlane__) */

