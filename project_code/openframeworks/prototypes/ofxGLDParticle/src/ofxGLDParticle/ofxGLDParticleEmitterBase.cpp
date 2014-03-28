//
//  ofGLDParticleEmitterBase.cpp
//  ofxGLDParticle
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#include "ofxGLDParticleEmitterBase.h"


ofxGLDParticleEmitterBase::ofxGLDParticleEmitterBase(){
    maxParticles = 1000;
    
    lifeSpan = 100;
    lifeSpanVariance = 10;
    
    emitAngle = 0;
    emitAngleVariance = 360;
    startSpeed = 5;
    startSpeedVariance = 5;
    
    radialAcceleration = -0.1;
    radialAccelerationVariance = -0.01;
    
    startSize = 1;
    finishSize = 1;
    
    startRed = 255;
    startGreen = 255;
    startBlue = 255;
    startAlpha = 255;
    finishRed = 255;
    finishGreen = 255;
    finishBlue = 0;
    finishAlpha = 0;
    
    friction = 0.99;
    frictionVariance = 0;
}



void ofxGLDParticleEmitterBase::update(){
    int index = 0;
    
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        it->update();
        if(it->lifeSpan<1){
            it = particles.erase(it);
        }else{
            //next
            it++;
        }
    }
}



void ofxGLDParticleEmitterBase::draw(){
    //Override here for custom drawing
    ofSetColor(255);
    list<ofxGLDParticleBase2D>::iterator it = particles.begin();
    while(it!=particles.end()){
        ofSetColor(it->red, it->green, it->blue, it->alpha);
        ofLine(it->position.x, it->position.y, it->prevPosition.x - it->velocity.x*3, it->prevPosition.y - it->velocity.y*3);
        it++;
    }
}



//Remove all particles
void ofxGLDParticleEmitterBase::removeAllParticles(){
    particles.clear();
}



void ofxGLDParticleEmitterBase::addParticles(float x, float y, int num){
    for(int i=0; i<num; i++){
        addParticle(x,y);
    }
}



void ofxGLDParticleEmitterBase::addParticle(float x, float y){
    if(particles.size() < maxParticles){
        ofxGLDParticleBase2D p;
        p.lifeSpan = lifeSpan + ofRandom(lifeSpanVariance);
        
        float nLifeSpan = 1 / (float)p.lifeSpan;
        float emitRad = (emitAngle + ofRandom(emitAngleVariance)) * M_PI / 180.0;
        float speed = startSpeed + ofRandom(startSpeedVariance);
        float accel = radialAcceleration + ofRandom(radialAccelerationVariance);
        
        p.position = ofVec2f(x,y);
        p.rotation = startRotation + ofRandom(startRotationVariance);
        p.rotationOffset = (endRotation + ofRandom(endRotationVariance) - p.rotation)*nLifeSpan;
        p.velocity = ofVec2f(cos(emitRad)*speed, sin(emitRad)*speed);
        p.gravity = gravity;
        p.radialAcceleration = ofVec2f(cos(emitRad)*accel, sin(emitRad)*accel);
        p.friction = friction + ofRandom(frictionVariance);
        p.size = startSize + ofRandom(startSizeVariance);
        p.sizeOffset = (finishSize + ofRandom(finishSizeVariance) - p.size) * nLifeSpan;
        p.red = startRed + ofRandom(startRedVariance);
        p.redOffset =  (finishRed + ofRandom(finishRedVariance) - p.red) * nLifeSpan;
        p.green = startGreen + ofRandom(startGreenVariance);
        p.greenOffset =  (finishGreen + ofRandom(finishGreenVariance) - p.green) * nLifeSpan;
        p.blue = startBlue + ofRandom(startBlueVariance);
        p.blueOffset =  (finishBlue + ofRandom(finishBlueVariance) - p.blue) * nLifeSpan;
        p.alpha = startAlpha + ofRandom(startAlphaVariance);
        p.alphaOffset =  (finishAlpha + ofRandom(finishAlphaVariance) - p.alpha) * nLifeSpan;
        
        particles.push_back(p);
    }else{
        //Ignore too much particle
        //cout << "Particle is full" << endl;
    }
}
