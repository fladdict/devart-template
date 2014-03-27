//
//  FloorSystemRangeSensor.cpp
//  TheGiantMap
//
//  Created by 深津 貴之 on 2014/03/03.
//
//

#include "FloorSystemRangeSensor.h"

ofxRangeSensor sensor0;

FloorSystemRangeSensor::FloorSystemRangeSensor(){
    
}


void FloorSystemRangeSensor::setup(string portName, int speed){
    cout << "FloorSystemRangeSensor setup" << endl;
    //Setup Grid
    ofxRangeSensorGrid grid;
    grid.x = 0;
    grid.y = 0;
    grid.width = 2;
    grid.height = 2;
    grid.nodeNumX = 101;
    grid.nodeNumY = 101;
    
    sensorManager.setup(grid);
    
    sensor0;
    char connect_address[] = "192.168.0.10";
    int port0 = 10940;
    
    sensor0.position.x = -0.1;
    sensor0.position.y = -0.1;
    sensor0.rotation = 45;
    sensor0.scanAngle = 270;
    sensor0.setup(connect_address, port0);
    sensor0.open();
    
    sensorManager.addSensor(sensor0);
}


void FloorSystemRangeSensor::update(){
    sensorManager.update();
}


void FloorSystemRangeSensor::draw(){
    sensorManager.draw();
}
