//
//  Node.h
//  TheGiantMap01
//
//  Created by 深津 貴之 on 2014/02/11.
//
//


#ifndef __TheGiantMap01__Node__
#define __TheGiantMap01__Node__

#include "ofMain.h"
#include <iostream>

class Node{
    public :
    Node();
    ofVec3f initialPosition;
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f force;
    ofColor color;
    
    float x;
    float y;
    float z;
    float initialX;
    float initialY;
    float initialZ;
    float vx;
    float vy;
    float vz;
    float fx;
    float fy;
    float fz;
    float friction;
    
    //EarthShake
    float shakeCount;
    ofVec3f shake;
};


#endif /* defined(__TheGiantMap01__Node__) */




