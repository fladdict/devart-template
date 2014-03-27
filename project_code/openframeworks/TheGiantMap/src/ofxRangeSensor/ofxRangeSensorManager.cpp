//
//  ofxRangeSensorManager.cpp
//  ofxRangeSensor
//
//  Created by 深津 貴之 on 2014/02/28.
//
//

#include "ofxRangeSensorManager.h"


ofxRangeSensorManager::ofxRangeSensorManager(){
    
}


void ofxRangeSensorManager::setup(ofxRangeSensorGrid grid){
    sensorGrid = grid;
    pixels = (unsigned char *)malloc(sizeof(unsigned char)*sensorGrid.nodeNumX*sensorGrid.nodeNumY);
}



void ofxRangeSensorManager::tearDown(){
    sensors.clear();
    free(pixels);
}


void ofxRangeSensorManager::update(){
    resetGrid();
    updateSensor();
}

void ofxRangeSensorManager::updateSensor(){
    //SetupRandomNumber
    for(int i=0; i<sensors.size(); i++){
        ofxRangeSensor *sensor = &sensors[i];
        if(sensor->isOpen){
            sensor->update();
            
            for(int j=0; j<sensor->scanStep; j++){
                ofVec2f grid = convertPositionToGridNode(convertSensorStepToPosition(sensor, j));
                if(grid.x>=0 && grid.y>=0 && grid.x<sensorGrid.nodeNumX && grid.y<sensorGrid.nodeNumY){
                    int index = grid.y * sensorGrid.nodeNumX + grid.x;
                    
                    updateGridTile(grid.x-1, grid.y-1);
                    updateGridTile(grid.x, grid.y-1);
                    updateGridTile(grid.x+1, grid.y-1);
                    updateGridTile(grid.x-1, grid.y);
                    updateGridTile(grid.x, grid.y);
                    updateGridTile(grid.x+1, grid.y);
                    updateGridTile(grid.x-1, grid.y+1);
                    updateGridTile(grid.x, grid.y+1);
                    updateGridTile(grid.x+1, grid.y+1);
                }
            }
        }
    }
}

void ofxRangeSensorManager::updateGridTile(int x, int y){
    if(x<0)
        return;
    
    if(y<0)
        return;
    
    if(x>sensorGrid.nodeNumX-1)
        return;
    
    if(y>sensorGrid.nodeNumY-1)
        return;
    
    int index = y * sensorGrid.nodeNumX + x;
    int val = pixels[index];
    pixels[index] = val * 0.25 + 255 * 0.75;
}



ofVec2f ofxRangeSensorManager::convertSensorStepToPosition(ofxRangeSensor *sensor, int step){
    float dist = sensor->data[step] / 1000.0;  //convert to mili metor to meter.
    float angle = sensor->stepToGlobalAngle(step);
    float rad = angle * M_PI / 180.0;
    float xx = sensor->position.x + cos(rad)*dist;
    float yy = sensor->position.y + sin(rad)*dist;
    return ofVec2f(xx, yy);
}


ofVec2f ofxRangeSensorManager::convertPositionToGridNode(ofVec2f position){
    position.x -= sensorGrid.x;
    position.y -= sensorGrid.y;
    int gridX = round(ofMap(position.x, 0, sensorGrid.width, 0, sensorGrid.nodeNumX-1));
    int gridY = round(ofMap(position.y, 0, sensorGrid.height, 0, sensorGrid.nodeNumY-1));
    return ofVec2f(gridX,gridY);
}


void ofxRangeSensorManager::resetGrid(){
    int n = sensorGrid.nodeNumY * sensorGrid.nodeNumX;
    for(int i=0; i<n; i++){
        pixels[i] = 0;
    }
}



#pragma mark - Blob Management






#pragma mark - Sensor

void ofxRangeSensorManager::addSensor(ofxRangeSensor sensor){
    sensors.push_back(sensor);
}




#pragma mark - Draw

void ofxRangeSensorManager::draw(){
    for(int i=0; i<sensors.size(); i++){
        ofxRangeSensor *sensor = (ofxRangeSensor*)&sensors[i];
        drawSensor(sensor);
    }
    
    
    float gridW = sensorGrid.width / (sensorGrid.nodeNumX-1);
    float gridH = sensorGrid.height / (sensorGrid.nodeNumY-1);
    for(int yy=0; yy<sensorGrid.nodeNumY; yy++){
        for(int xx=0; xx<sensorGrid.nodeNumX; xx++){
            int index = yy*sensorGrid.nodeNumX + xx;
            ofSetColor(200);
            ofEllipse(xx*gridW, yy*gridH, 0.01, 0.01);

        }
    }
    
    //contourFinder.draw(0,0,2,2);
}


void ofxRangeSensorManager::drawSensor(ofxRangeSensor *sensor){
    
    /*
    if(sensor->isOpen){
        ofSetColor(255,0,0,80);
        for(int j=0; j<sensor->scanStep; j++){
            float angle = sensor->stepToGlobalAngle(j);
            float x0 = sensor->position.x;
            float y0 = sensor->position.y;
            float dist = sensor->data[j] / 1000.0;
            float x1 = x0 + cos(angle*M_PI/180.0) * dist;
            float y1 = y0 + sin(angle*M_PI/180.0) * dist;
            ofLine(x0, y0, x1, y1);
        }
    }*/
    
    //Draw Sensor
    ofSetColor(255,255,0);
    ofEllipse(sensor->position.x, sensor->position.y,  0.05, 0.05);
}




