//
//  ofxGLDSpringNode.h
//  ofxGLDSpring
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#pragma once

#ifndef __ofxGLDSpring__ofxGLDSpringNode__
#define __ofxGLDSpring__ofxGLDSpringNode__

#include "ofMain.h"

class ofxGLDSpringNode{
    public:
        ofxGLDSpringNode();
        //ofxGLDSpringNode(float x, float y, bool isFixed);
        void update();
        void draw();
    
        ofVec3f position;
        ofVec3f velocity;
        ofVec3f focrce;
        bool isFixed;
        float friction;
        float maxVelocity;
};

#endif /* defined(__ofxGLDSpring__ofxGLDSpringNode__) */
