//
//  FloorSystemSwitch.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#include "FloorSystemSwitch.h"


FloorSystemSwitch::FloorSystemSwitch(){
    
}

void FloorSystemSwitch::update(){
    if(ofRandom(0,1)<0.01){
        cout << "notify" << endl;
        notifyEvent(ofRandom(0,1), ofRandom(0,1));
    }
}