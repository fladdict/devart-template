//
//  Cloud.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#include "Cloud.h"

Cloud::Cloud(){
    
}


void Cloud::setup(){
    repositionDist = sqrt(ofGetWidth()*ofGetWidth()+ofGetHeight()*ofGetHeight()) * 1.7;
    images[0].loadImage("texture-cloud.png");
    images[1].loadImage("texture-cloud-1.png");
    images[2].loadImage("texture-cloud-2.png");
    resetPosition();
}

void Cloud::update(){
    position += velocity;
    
    //Reset if cloud is outside of screen
    float dx = position.x - ofGetWidth()*0.5;
    float dy = position.y - ofGetHeight()*0.5;
    float dist = sqrt(dx*dx+dy*dy);
    if(dist > repositionDist){
        resetPosition();
    }
}


void Cloud::addPositionOffset(float x, float y)
{
    position.x += x;
    position.y += y;
}


void Cloud::resetPosition(){
    textureIndex = floor(ofRandom(0,3));
    velocity.x = (ofRandom(0.5,2)+ofRandom(0.5,2)) * 0.5;
    velocity.y = (ofRandom(0.5,2)+ofRandom(0.5,2)) * 0.5;
    scale.x = (ofRandom(0.5,2)+ofRandom(0.5,2)+ofRandom(0.5,2)+ofRandom(0.5,2))/4;
    scale.y = (ofRandom(0.5,2)+ofRandom(0.5,2)+ofRandom(0.5,2)+ofRandom(0.5,2))/4;
    rotation = ofRandom(0,360);
    alpha = ofRandom(100,200);
    
    //SetupPosition
    float requiredDist = 1000;
    float rad = ofRandom(180,300) * M_PI / 180.0;
    
    position.x = ofGetWidth()*0.5 + cos(rad)*repositionDist;
    position.y = ofGetHeight()*0.5 + sin(rad)*repositionDist;
}

void Cloud::draw(){
    ofPushMatrix();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofEnableAlphaBlending();
    //
    ofTranslate(position.x, position.y,0);
    ofRotate(rotation);
    ofScale(scale.x, scale.y);
    ofTranslate(-images[0].width*0.5, -images[0].height*0.5);
    //
    ofSetColor(255,255,255,alpha);
    images[textureIndex].draw(0,0,images[0].width,images[0].height);
    ofDisableAlphaBlending();
    ofDisableBlendMode();
    ofPopMatrix();
}
