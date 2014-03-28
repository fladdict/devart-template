//
//  FloorSystemSwitch.h
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#pragma once

#ifndef __TheGiantMap__FloorSystemSwitch__
#define __TheGiantMap__FloorSystemSwitch__

#include "ofMain.h"
#include "FloorSystemInterface.h"
#include <iostream>

class FloorSystemSwitch : public FloorSystemInterface{
    public:
        FloorSystemSwitch();
        virtual void update();
};

#endif /* defined(__TheGiantMap__FloorSystemSwitch__) */
