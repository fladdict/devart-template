//
//  ofxGLDParticleBase2D.cpp
//  ofxGLDParticle
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#include "ofxGLDParticleBase2D.h"

ofxGLDParticleBase2D::ofxGLDParticleBase2D(){
}

void ofxGLDParticleBase2D::update(){
    lifeSpan--;
    
    //Transform
    prevPosition = position;
    velocity += radialAcceleration;
    velocity += gravity;
    velocity *= friction;
    position += velocity;
    size += sizeOffset;
    rotation += rotationOffset;
    
    //Color
    red += redOffset;
    green += greenOffset;
    blue += blueOffset;
    alpha += alphaOffset;
}
