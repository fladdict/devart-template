//
//  SoundManager.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/02/18.
//
//

#ifndef __TheGiantMap__SoundManager__
#define __TheGiantMap__SoundManager__

#include "ofMain.h"
#include <iostream>


class SoundManager{
public:
    SoundManager();
    void setup();
    void playShakeSound();
    vector <ofSoundPlayer> stepSounds;
};

#endif /* defined(__TheGiantMap__SoundManager__) */
