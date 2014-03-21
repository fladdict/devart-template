//
//  Node.cpp
//  TheGiantMap01
//
//  Created by 深津 貴之 on 2014/02/11.
//
//

#include "Node.h"

Node::Node()
{
    position = ofVec3f(0.0,0.0,0.0);
    initialPosition = ofVec3f(0.0,0.0,0.0);
    velocity = ofVec3f(0.0,0.0,0.0);
    force = ofVec3f(0.0,0.0,0.0);
    shakeCount = 0;
    x = y = z = 0;
    initialX = initialY = initialZ = 0;
    vx = vy = vz = 0;
    fx = fy = fz = 0;
}