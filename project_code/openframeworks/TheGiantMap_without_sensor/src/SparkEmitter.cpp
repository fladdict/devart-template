//
//  SparkEmitter.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#include "SparkEmitter.h"

SparkEmitter::SparkEmitter(){
    lifeSpan = 40;
    startSpeed = 5;
    startSpeedVariance = 5;
    
    startRed = 200;
    startRedVariance = 50;
    startGreen = 150;
    startGreenVariance = 50;
    startBlue = 100;
    startBlueVariance = 50;
    startAlpha = 20;
    finishAlpha = 0;
    startRadialPositionOffset = 20;
    startRadialPositionOffsetVariance = 10;
    
    friction = 0.9;
    frictionVariance = 0.02;
    
    finishRed = 50;
    finishGreen = 50;
    finishBlue = 100;

}

void SparkEmitter::draw(){
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        ofSetColor(it->red, it->green, it->blue, it->alpha);
        ofLine(it->position.x, it->position.y, it->prevPosition.x - it->velocity.x*2, it->prevPosition.y - it->velocity.y*2);
        it++;
    }
    ofDisableBlendMode();
    ofDisableAlphaBlending();
}