//
//  ofGLDParticleEmitterBase.h
//  ofxGLDParticle
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#pragma once

#ifndef __ofxGLDParticle__ofxGLDParticleEmitterBase__
#define __ofxGLDParticle__ofxGLDParticleEmitterBase__

#include "ofxGLDParticleBase2D.h"
#include <iostream>


class ofxGLDParticleEmitterBase{
    public:
        ofxGLDParticleEmitterBase();
        virtual void update();
        virtual void draw();
    
        virtual void addParticles(float x, float y, int num);
        virtual void addParticle(float x, float y);
        virtual void removeAllParticles();
    
    
        enum {PARTICLE_MODE_OFFSET, PARTICLE_MODE_FINISH};
    
        float alpha;
    
        //int variance
        int maxParticles;
        int lifeSpan;
        int lifeSpanVariance;
    
        int textureNum;
    
        //Start direction
        float emitAngle;
        float emitAngleVariance;
    
        //Speed
        float startSpeed;
        float startSpeedVariance;
    
    
    
        //Rotation
        float startRotation;
        float startRotationVariance;
        int rotationMode;
        float rotationOffset;
        float rotationOffsetVariance;
        float finishRotation;
        float finishRotationVariance;
    
        //Power
        float friction;
        float frictionVariance;
        ofVec2f gravity;
        float radialAcceleration;
        float radialAccelerationVariance;
        float startRadialPositionOffset;
        float startRadialPositionOffsetVariance;
    
        //Size
        float startSize;
        float startSizeVariance;
        float finishSize;
        float finishSizeVariance;
    
        //Colors
        float startRed;
        float startRedVariance;
        float finishRed;
        float finishRedVariance;
        float startGreen;
        float startGreenVariance;
        float finishGreen;
        float finishGreenVariance;
        float startBlue;
        float startBlueVariance;
        float finishBlue;
        float finishBlueVariance;
        float startAlpha;
        float startAlphaVariance;
        float finishAlpha;
        float finishAlphaVariance;
    
        list <ofxGLDParticleBase2D> particles;
};

#endif /* defined(__ofxGLDParticle__ofxGLDParticleEmitterBase__) */
