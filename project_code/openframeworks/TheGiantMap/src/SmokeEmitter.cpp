//
//  SmokeEmitter.cpp
//  TheGiantMap_Sketch01
//
//  Created by 深津 貴之 on 2014/02/16.
//
//

#include "SmokeEmitter.h"



SmokeEmitter::SmokeEmitter()
{
}

void SmokeEmitter::setup()
{
    textureImages[0].loadImage("texture-smoke-0.png");
    textureImages[1].loadImage("texture-smoke-1.png");
    textureImages[2].loadImage("texture-smoke-2.png");
    textureImages[3].loadImage("texture-smoke-3.png");
    
    lifeSpan = 25;
    startAlpha = 128;
    startAlphaVariance = 128;
    finishAlpha = 0.0;
    startSize = 0.25;
    startSizeVariance = 0.5;
    finishSize = 0.5;
    finishSizeVariance = 0.25;
    textureNum = 4;
    
    startRotation = 0;
    startRotationVariance = 360;
    finishRotation = 0;
    finishRotationVariance = 360;
    
    startSpeed = 1;
    startSpeedVariance = 10;
    radialAcceleration = 0.1;
    friction = 0.8;
    radialAccelerationVariance = 0;
}


void SmokeEmitter::draw()
{
    ofEnableAlphaBlending();
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it != particles.end()){
        ofImage *tex = &textureImages[it->textureIndex];
        float woff = tex->width * 0.5;
        float hoff = tex->height * 0.5;
        ofPushMatrix();
        ofSetColor(255, 255, 255, it->alpha);
        ofTranslate(it->position.x, it->position.y);
        ofScale(it->size, it->size);
        ofRotate(it->rotation);
        ofTranslate(-woff, -hoff);
        tex->draw(0,0);
        ofPopMatrix();
        it++;
    }
    
    ofDisableAlphaBlending();
}
