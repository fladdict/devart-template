//
//  NightShader.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/23.
//
//

#include "NightShader.h"



NightShader::NightShader(){
    
}


void NightShader::setup(int width, int height){
    blurXShader.load("shaders/simpleVertex.vert", "shaders/blurX.frag");
    blurYShader.load("shaders/simpleVertex.vert", "shaders/blurY.frag");
    nightShader.load("shaders/simpleVertex.vert", "shaders/night.frag");
    blurOnePass.allocate(width, height);
    blurTowPass.allocate(width, height);
    plane.set(width, height, 2, 2);
    plane.mapTexCoords(0, 0, width, height);
    fboWidth = width;
    fboHeight = height;
    rad = 0;
}


ofFbo* NightShader::applyEffect(ofFbo *sourceFbo, ofFbo *destFbo){
    float blur = (ofRandom(0.8,1.2)+ofRandom(0.8,1.2)+ofRandom(0.8,1.2)+ofRandom(0.8,1.2))/4.0;
    blurOnePass.begin();
        blurXShader.begin();
            blurXShader.setUniform1f("blurAmnt", blur);
            sourceFbo->draw(0,0);
        blurXShader.end();
    blurOnePass.end();
    
    blurTowPass.begin();
        blurYShader.begin();
            blurYShader.setUniform1f("blurAmnt", blur);
            blurOnePass.draw(0,0);
        blurYShader.end();
    blurTowPass.end();
    
    rad += (ofRandom(0.05, 0.1)+ofRandom(0.05, 0.1)+ofRandom(0.05, 0.1)) / 3.0;
    if(rad>M_PI*2)
        rad = 0;
    
    destFbo->begin();
    nightShader.begin();
    ofPushMatrix();
    ofSetColor(255);
    nightShader.setUniformTexture("tex0", sourceFbo->getTextureReference(), 1);
    nightShader.setUniformTexture("tex1", blurTowPass.getTextureReference(), 2);
    nightShader.setUniform1f("overlayAlpha", overlayAlpha);
    nightShader.setUniform1f("lightOffset", (cos(rad)+1)*0.5 * ofRandom(0.5,1.5));
    ofTranslate(fboWidth*0.5, fboHeight*0.5);
    plane.draw();
    ofPopMatrix();
    nightShader.end();
    destFbo->end();
    
    return destFbo;
}

//Overlay
// col = col1/255 * (col1 + 2*col0/255 * (255-col1))