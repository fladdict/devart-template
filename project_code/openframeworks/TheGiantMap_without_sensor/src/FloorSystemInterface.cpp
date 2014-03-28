//
//  FloorSystemInterface.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#include "FloorSystemInterface.h"


FloorSystemInterface::FloorSystemInterface(){
    
}


void FloorSystemInterface::setup(){
    
}

void FloorSystemInterface::update(){
    
}


void FloorSystemInterface::notifyEvent(float x, float y){
    ofVec2f vec = ofVec2f(x,y);
    ofNotifyEvent(floorTouched, vec, this);
}
