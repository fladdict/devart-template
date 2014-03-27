//
//  CrackParticleEmitter.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/17.
//
//

#pragma once

#ifndef __TheGiantMap__CrackParticleEmitter__
#define __TheGiantMap__CrackParticleEmitter__

#include "ofMain.h"
#include "ofxGLDParticleEmitterBase.h"
#include <iostream>

class CrackParticleEmitter : public ofxGLDParticleEmitterBase
{
public:
    CrackParticleEmitter();
    void setup();
    void draw();
    void addPositionOffset(float x, float y);
    
    ofImage textureImages[4];
};

#endif /* defined(__TheGiantMap__CrackParticleEmitter__) */
