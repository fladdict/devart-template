//
//  HazeEmitter.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/07.
//
//

#include "HazeEmitter.h"


HazeEmitter::HazeEmitter(){
    textureImages[0].loadImage("texture-haze-0.png");
    textureImages[1].loadImage("texture-haze-1.png");
    textureImages[2].loadImage("texture-haze-2.png");
    textureImages[3].loadImage("texture-haze-0.png");
    
    maxParticles = 1000;
    lifeSpan = 300;
    textureNum = 4;
    
    emitAngle = 22.5;
    emitAngleVariance = 45;
    startSpeed = 2;
    startSpeedVariance = 10;
    
    radialAcceleration = 0;
    radialAccelerationVariance = 0;
    
    startRotation = 0;
    startRotationVariance = 360;
    
    startSize = 1.0;
    startSizeVariance = 1.0;
    finishSize = 1.5;
    finishSizeVariance = 1.0;
    
    startRed = 255;
    startRedVariance = 0;
    startGreen = 255;
    startGreenVariance = 0;
    startBlue = 255;
    startBlueVariance = 0;
    startAlpha = 25;
    startAlphaVariance = 25;
    finishAlpha = 0;
}


void HazeEmitter::update(){
    alpha += (tAlpha-alpha)*0.01;
    ofxGLDParticleEmitterBase::update();
    
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        //delete if outside
        if(it->position.x > ofGetWidth()*1.2 || it->position.y > ofGetHeight()*1.2){
            it->lifeSpan = 0;
        }
        it++;
    }
}


void HazeEmitter::draw()
{
    float a = alpha / 255.0;
    ofEnableAlphaBlending();
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it != particles.end()){
        ofImage *tex = &textureImages[it->textureIndex];
        float woff = tex->width * 0.5;
        float hoff = tex->height * 0.5;
        ofPushMatrix();
        ofSetColor(255, 255, 255, it->alpha*a);
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


//Override start position
void HazeEmitter::addParticle(float x, float y){
    ofxGLDParticleEmitterBase::addParticle(x, y);
    list<ofxGLDParticleBase2D>::iterator it = particles.end();
    it--;
    if(ofRandom(0,1)<0.5){
        it->position.x = -200;
        it->position.y = ofRandom(0,ofGetHeight());
    }else{
        it->position.x = ofRandom(0,ofGetWidth());
        it->position.y = -200;
    }
}