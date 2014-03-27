//
//  CrackParticleEmitter.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/17.
//
//

#include "CrackParticleEmitter.h"



CrackParticleEmitter::CrackParticleEmitter(){
    
}


void CrackParticleEmitter::setup(){
    lifeSpan = 450;
    startSpeed = 0;
    startRotation = 0;
    radialAcceleration = 0;
    radialAccelerationVariance = 0;
    startRotationVariance = 0;
    textureNum = 4;
    
    startAlpha = 256;
    finishAlpha = 0;
    
    rotationMode = PARTICLE_MODE_OFFSET;
    startRotation = 0;
    startRotationVariance = 360;
    rotationOffset = 0;
    rotationOffsetVariance = 0;
    
    textureImages[0].loadImage("crack0.png");
    textureImages[1].loadImage("crack1.png");
    textureImages[2].loadImage("crack2.png");
    textureImages[3].loadImage("crack3.png");
}


void CrackParticleEmitter::addPositionOffset(float x, float y){
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        it->position += ofVec2f(x,y);
        it++;
    }
}


void CrackParticleEmitter::draw(){
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        ofImage *img = &textureImages[it->textureIndex];
        float woff = img->width * 0.5;
        float hoff = img->height * 0.5;
        
        ofPushMatrix();
        ofSetColor(255,255,255,it->alpha);
        ofTranslate(it->position.x, it->position.y);
        ofScale(0.5,0.5);
        ofRotate(it->rotation);
        ofTranslate(-woff, -hoff);
        img->draw(0,0);
        
        ofPopMatrix();
        
        it++;
    }
}
