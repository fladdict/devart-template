//
//  NightShader.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/23.
//
//

#ifndef __TheGiantMap__NightShader__
#define __TheGiantMap__NightShader__

#include "ofMain.h"
#include <iostream>

class NightShader{
    public:
    NightShader();
    void setup(int width, int height);
    ofFbo* applyEffect(ofFbo *sourceFbo, ofFbo *destFbo);
    
    float overlayAlpha;
    float fboWidth;
    float fboHeight;
    float rad;
    ofPlanePrimitive plane;
    
    ofShader blurXShader;
    ofShader blurYShader;
    ofShader nightShader;
    ofFbo blurOnePass;
    ofFbo blurTowPass;
};

#endif /* defined(__TheGiantMap__NightShader__) */
