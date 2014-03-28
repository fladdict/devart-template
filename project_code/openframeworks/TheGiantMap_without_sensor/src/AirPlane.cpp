//
//  AirPlane.cpp
//  TheGiantMap_Sketch01
//
//  Created by 深津 貴之 on 2014/02/16.
//
//

#include "AirPlane.h"

vector <AirPlaneSmoke> smokes;

AirPlane::AirPlane(){
    
}

void AirPlane::setup(){
    repositionDist = sqrt(ofGetWidth()*ofGetWidth()+ofGetHeight()*ofGetHeight()) * 1.2;
    image.loadImage("texture-airplane.png");
    smokeImage.loadImage("texture-airplane-smoke.png");
    resetPosition();
}

void AirPlane::resetPosition()
{
    float rad = ofRandom(0,1)*M_PI;
    position.x = cos(rad)*repositionDist + ofGetWidth()*0.5;
    position.y = sin(rad)*repositionDist + ofGetHeight()*0.5;
    rad *= ofRandom(0.83333, 1.2);
    velocity.x = -cos(rad)*1;
    velocity.y = -sin(rad)*1;
}

void AirPlane::explode(){
    //
    resetPosition();
}

void AirPlane::addPositionOffset(float x, float y){
    position.x += x;
    position.y += y;
    for(int i=0; i<smokes.size(); i++){
        smokes[i].addPositionOffset(x, y);
    }
}

void AirPlane::update(){
    position += velocity;
    
    //reset if its outside of the screen
    float dx = ofGetWidth()*0.5 - position.x;
    float dy = ofGetHeight()*0.5 - position.y;
    float d = sqrt(dx*dx+dy*dy);
    if(d>repositionDist){
        resetPosition();
    }
    
    //Generate Smoke
    //for(int i=0; i<2; i++){
    AirPlaneSmoke smk;
    smk.position.x = position.x;
    smk.position.y = position.y;
    smokes.push_back(smk);
    //}
    
    for(int i=smokes.size()-1; i>-1; i--){
        smokes[i].update();
        if(smokes[i].lifeCount<1){
            smokes.erase(smokes.begin()+i);
        }
    }
}

void AirPlane::draw(){
    float w = image.width;
    float h = image.height;
    float rad = atan2(velocity.y, velocity.x);
    
    ofEnableAlphaBlending();
    for(int i=smokes.size()-1; i>-1; i--){
        AirPlaneSmoke *s = &smokes[i];
        ofPushMatrix();
        ofSetColor(255,255,255,s->lifeCount * 0.06);
        ofTranslate(s->position.x, s->position.y);
        ofScale(s->scale, s->scale);
        ofTranslate(-5,-5);
        smokeImage.draw(0,0,10,10);
        ofPopMatrix();
    }
    
    
    ofSetColor(255, 255, 255, 255);
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    ofRotateZ(rad*180/3.141592);
    ofScale(0.25, 0.25);
    
    ofTranslate(-w*0.5, -h*0.5);
    image.draw(0, 0, w, h);
    ofPopMatrix();
    
    ofDisableAlphaBlending();
}



/*************************
    Smoke
**************************/

AirPlaneSmoke::AirPlaneSmoke(){
    lifeCount = 400;
    alpha = 255;
    scale = ofRandom(0.5,1);
}

void AirPlaneSmoke::addPositionOffset(float x, float y){
    position.x += x;
    position.y += y;
}

void AirPlaneSmoke::update(){
    lifeCount--;
    scale += 0.002;
    position += ofVec3f(ofRandom(-0.2, 0.2), ofRandom(-0.2, 0.2),0);
}

void AirPlaneSmoke::draw(){
    
}