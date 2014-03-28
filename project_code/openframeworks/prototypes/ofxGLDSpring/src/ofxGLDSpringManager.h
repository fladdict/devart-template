//
//  ofxGLDSpringManager.h
//  ofxGLDSpring
//
//  Created by 深津 貴之 on 2014/02/19.
//
//

#ifndef __ofxGLDSpring__ofxGLDSpringManager__
#define __ofxGLDSpring__ofxGLDSpringManager__

#include "ofMain.h"
#include "ofxGLDSpringNode.h"
#include "ofxGLDSpring.h"
#include <iostream>

class ofxGLDSpringManager{
    public:
        ofxGLDSpringManager();
        void update();
        void updateForce();
        void resetForce();
        void updateNodes();
        void draw();
    
        //void addSpring(ofxGLDSpring &spring);
        //void removeSpring(ofxGLDSpring &spring);
        void addNode(ofxGLDSpringNode &node);
        void removeNode(ofxGLDSpringNode &node);
    
        list <ofxGLDSpring> springs;
        list <ofxGLDSpringNode> nodes;
};

#endif /* defined(__ofxGLDSpring__ofxGLDSpringManager__) */
