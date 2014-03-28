//
//  SparkEmitter.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/01.
//
//

#ifndef __TheGiantMap__SparkEmitter__
#define __TheGiantMap__SparkEmitter__

#include "ofxGLDParticleEmitterBase.h"
#include <iostream>

class SparkEmitter : public ofxGLDParticleEmitterBase{
    public:
        SparkEmitter();
        void draw();
};

#endif /* defined(__TheGiantMap__SparkEmitter__) */
