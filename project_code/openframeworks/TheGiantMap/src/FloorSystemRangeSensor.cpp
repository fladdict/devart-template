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
    
    //Fortesting versino we use sensor plan b 
    sensor0.position.x = 2.1;//-0.1;
    sensor0.position.y = 2.1;//-0.1;
    sensor0.rotation = 225;//45;
    sensor0.scanAngle = 270;
    sensor0.setup(connect_address, port0);
    sensor0.open();
    
    sensorManager.addSensor(sensor0);
    
    
    //Create Grid
    gridNumX = 31;
    gridNumY = 31;
    tiles = (float*)malloc(sizeof(float)*gridNumX*gridNumY);
    fired = (bool*)malloc(sizeof(bool)*gridNumX*gridNumY);
    int n = gridNumY * gridNumX;
    for(int i=0; i<n; i++){
        tiles[i] = 0;
        fired[i] = false;
    }
}

void FloorSystemRangeSensor::tearDown(){
    sensorManager.tearDown();
    free(tiles);
    free(fired);
}


void FloorSystemRangeSensor::update(){
    sensorManager.update();
    
    //Map pixels to tile
    int n = sensorManager.sensorGrid.nodeNumY * sensorManager.sensorGrid.nodeNumX;
    int xx = sensorManager.sensorGrid.nodeNumX;
    int yy = sensorManager.sensorGrid.nodeNumY;
    
    for(int y=0; y<yy; y++){
        for(int x=0; x<xx; x++){
            int pixelIndex = y * xx + x;
            
            float val = sensorManager.pixels[pixelIndex];
            //convert pixel index to tile index;
            int tileX = round(ofMap(x, 0, xx, 0, gridNumX));
            int tileY = round(ofMap(y, 0, yy, 0, gridNumY));
            int tileIndex = tileY*gridNumX+tileX;
            tiles[tileIndex] += val;
        }
    }
    
    //updat tiles
    n = gridNumX * gridNumY;
    for(int i=0; i<n; i++){
        tiles[i] *= 0.5;
        if(tiles[i]>2200 && fired[i]==false){
            //fire
            fired[i]=true;
            float x = (floor(i / gridNumX)) / (float)gridNumY;
            float y = (i % gridNumX) / (float)gridNumX;
            //cout << x << " " << y << endl;
            notifyEvent(x,y);
        }else if(tiles[i]<250){
            fired[i] = false;
        }
    }
}


void FloorSystemRangeSensor::draw(){
    
    ofPushMatrix();
    ofScale(ofGetWidth()/(float)sensorManager.sensorGrid.width,
            ofGetHeight()/(float)sensorManager.sensorGrid.height);
    
    sensorManager.draw();
    
    int xx = gridNumX;
    int yy = gridNumY;
    
    float dx = 1 / (float)(gridNumX-1) * sensorManager.sensorGrid.width;
    float dy = 1 / (float)(gridNumY-1) * sensorManager.sensorGrid.height;
    
    for(int y=0; y<yy; y++){
        for(int x=0; x<xx; x++){
            int tileIndex = y * xx + x;
            float val = tiles[tileIndex];
            if(fired[tileIndex]==true){
                ofSetColor(255, 255, 0);
                //cout << val << endl;
            }else{
                ofSetColor(100, 0, 0);
            }
            ofEllipse(x*dx, y*dy, val*0.00005, val*0.00005);
        }
    }
    
    ofPopMatrix();
}
