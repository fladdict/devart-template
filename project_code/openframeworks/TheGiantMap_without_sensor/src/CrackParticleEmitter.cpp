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
    lifeSpan = 900;
    startSpeed = 0;
    startRotation = 0;
    radialAcceleration = 0;
    radialAccelerationVariance = 0;
    startRotationVariance = 0;
    textureNum = 4;
    
    startAlpha = 512;
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
        ofRotate(it->rotation);
        ofTranslate(-woff, -hoff);
        img->draw(0,0);
        
        ofPopMatrix();
        
        it++;
    }
}

/*
void CrackParticleEmitter::addParticle(float x, float y){
    CrackParticle p;
    p.position = ofVec3f(x,y,0);
    p.lifeTime = p.maxLifeTime = 900;
    p.textureIndex = 0;
    particles.push_back(p);
}*/

/*
void CrackParticleEmitter::draw(){
    for(int i=0; i<particles.size();i++){
        particles[i].draw();
    }
}*/



/*
 CrackParticle::CrackParticle(){
 int num = int(ofRandom(0, 4));
 string name = "crack" + ofToString(num) + ".png";
 rotation = ofRandom(0, 360);
 image.loadImage(name);
 }
 
 void CrackParticle::setup(){
 ParticleBase::setup();
 }
 
 void CrackParticle::update(){
 ParticleBase::update();
 alpha = ofMap(lifeTime, 0, maxLifeTime, 0, 255,true);
 }
 
 void CrackParticle::addPositionOffset(float x, float y){
 position.x += x;
 position.y += y;
 }
 
 
 void CrackParticle::draw()
 {
 ofPushMatrix();
 ofSetColor(255,255,255,alpha);
 
 ofTranslate(position.x, position.y);
 ofRotate(rotation);
 ofTranslate(-image.width*0.5, -image.height*0.5);
 image.draw(0,
 0,
 image.width,
 image.height);
 
 ofPopMatrix();
 }
*/