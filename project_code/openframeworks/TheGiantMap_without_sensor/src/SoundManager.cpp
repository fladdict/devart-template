//
//  SoundManager.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/18.
//
//

#include "SoundManager.h"


SoundManager::SoundManager(){
}


void SoundManager::setup(){
    for(int i=0; i<3; i++){
        ofSoundPlayer sp;
        sp.loadSound("sound0.mp3");
        stepSounds.push_back(sp);
    }

}


void SoundManager::playShakeSound(){
    int soundIndex = int(ofRandom(0, stepSounds.size()));
    stepSounds[soundIndex].play();
}