//
//  ofxGLDSpring.h
//  ofxGLDSpring
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#pragma once

#ifndef __ofxGLDSpring__ofxGLDSpring__
#define __ofxGLDSpring__ofxGLDSpring__

#include "ofMain.h"
#include "ofxGLDSpringNode.h"

class ofxGLDSpring{
    public:
        ofxGLDSpring();
        //ofxGLDSpring(ofxGLDSpringNode &nd0, ofxGLDSpringNode &nd1);
        void update();
        void draw();
        float k;
        ofxGLDSpringNode node0;
        ofxGLDSpringNode node1;
};

#endif /* defined(__ofxGLDSpring__ofxGLDSpring__) */
