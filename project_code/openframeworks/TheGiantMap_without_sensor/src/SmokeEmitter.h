//
//  SmokeEmitter.h
//  TheGiantMap_Sketch01
//
//  Created by 深津 貴之 on 2014/02/16.
//
//

#ifndef __TheGiantMap_Sketch01__SmokeEmitter__
#define __TheGiantMap_Sketch01__SmokeEmitter__

#include "ofMain.h"
#include "ofxGLDParticleEmitterBase.h"
#include <iostream>

class SmokeEmitter : public ofxGLDParticleEmitterBase{
    public :
    SmokeEmitter();
    void setup();
    void draw();
    ofImage textureImages[4];
};

#endif /* defined(__TheGiantMap_Sketch01__SmokeEmitter__) */


