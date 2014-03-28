//
//  ofxGLDParticleBase2D.h
//  ofxGLDParticle
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#pragma once

#ifndef __ofxGLDParticle__ofxGLDParticleBase2D__
#define __ofxGLDParticle__ofxGLDParticleBase2D__

#include "ofMain.h"
#include <iostream>

class ofxGLDParticleBase2D{
    public:
    ofxGLDParticleBase2D();
    void reset();
    void update();
    
    int lifeSpan;
    
    ofVec2f position;
    ofVec2f prevPosition;
    ofVec2f velocity;
    ofVec2f gravity;
    ofVec2f radialAcceleration;
    float friction;
    
    //Transform
    float rotation;
    float rotationOffset;
    float size;
    float sizeOffset;
    
    //Colors
    float red;
    float green;
    float blue;
    float alpha;
    float redOffset;
    float greenOffset;
    float blueOffset;
    float alphaOffset;
};

#endif /* defined(__ofxGLDParticle__ofxGLDParticleBase2D__) */
