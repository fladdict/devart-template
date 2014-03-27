//
//  HazeEmitter.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/07.
//
//

#pragma once

#ifndef __TheGiantMap__HazeEmitter__
#define __TheGiantMap__HazeEmitter__

#include "ofxGLDParticleEmitterBase.h"
#include "ofMain.h"
#include <iostream>

class HazeEmitter : public ofxGLDParticleEmitterBase{
    public:
        HazeEmitter();
        virtual void update();
        virtual void draw();
        virtual void addParticle(float x, float y);
        ofImage textureImages[4];
        float tAlpha;
};

#endif /* defined(__TheGiantMap__HazeEmitter__) */
