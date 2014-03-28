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
    grayImage.allocate(sensorGrid.nodeNumX, sensorGrid.nodeNumY);
    grayImage.setFromPixels(pixels, sensorGrid.nodeNumX, sensorGrid.nodeNumY);
    
    data = (float*)malloc(sizeof(float)*sensorGrid.nodeNumX*sensorGrid.nodeNumY);
}



void ofxRangeSensorManager::tearDown(){
    sensors.clear();
    free(data);
    free(pixels);
}


void ofxRangeSensorManager::update(){
    resetGrid();
    updateSensor();
    updateOpenCv();
    
    //Add new CV detected blob to rangeSensorBlob
    //Delete missing blob
    //cout << "----------------" << endl;
    //cout << "Blobs: " << blobs.size() << endl;
    prepareUpdateBlobs();
    checkNewBlobs();
    deleteUnlinkedBlobs();
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
                    data[index] = 1;
                    
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
    
    int val = pixels[y * (int)sensorGrid.nodeNumX + x];
    pixels[y * (int)sensorGrid.nodeNumX + x] = val * 0.5 + 255 * 0.5;
}


void ofxRangeSensorManager::updateOpenCv(){
    grayImage.setFromPixels(pixels, sensorGrid.nodeNumX, sensorGrid.nodeNumY);
    grayImage.erode_3x3();
    grayImage.threshold(50);
    contourFinder.findContours(grayImage, 4, 50, 20, false, true);
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
        data[i] = 0;
        pixels[i] = 0;
    }
}



#pragma mark - Blob Management

void ofxRangeSensorManager::prepareUpdateBlobs(){
    vector<ofxRangeSensorBlob>::iterator it = blobs.begin();
    while(it!=blobs.end()){
        it->hasPairedCVBlob = false;
        it++;
    }
}

void ofxRangeSensorManager::checkNewBlobs(){
    vector<ofxCvBlob>::iterator cvbit = contourFinder.blobs.begin();
    while(cvbit != contourFinder.blobs.end()){
        vector<ofxRangeSensorBlob>::iterator rsbit = blobs.begin();
        vector<ofxRangeSensorBlob>::iterator nearestBlobit;
        float dist = positiveInfinity;
        while(rsbit != blobs.end()){
            float dx = rsbit->position.x - cvbit->centroid.x;
            float dy = rsbit->position.y - cvbit->centroid.y;
            float d = sqrt(dx*dx+dy*dy);
            if(d<dist){
                dist = d;
                nearestBlobit = rsbit;
            }
            rsbit++;
        }
        
        if(dist < 3){
            //cout << "Keep" << endl;
            nearestBlobit->position.x = cvbit->centroid.x;
            nearestBlobit->position.y = cvbit->centroid.y;
            nearestBlobit->hasPairedCVBlob = true;
        }else{
            ofxRangeSensorBlob b = getNewBlob();
            b.position.x = cvbit->centroid.x;
            b.position.y = cvbit->centroid.y;
            //cout << "New" << b.position.x << ", " << b.position.y << endl;
            b.hasPairedCVBlob = true;
            blobs.push_back(b);
        }
        
        cvbit++;
    }
}


void ofxRangeSensorManager::deleteUnlinkedBlobs(){
    vector<ofxRangeSensorBlob>::iterator it = blobs.begin();
    while(it!=blobs.end()){
        if(it->killCount>5){
            if(it->hasPairedCVBlob==false){
                //cout << "Delete" << it->position.x << ", " << it->position.y << endl;
                it = blobs.erase(it);
                continue;
            }
        }else{
            it->killCount+=1;
        }
        it++;
    }
}




ofxRangeSensorBlob ofxRangeSensorManager::getNewBlob(){
    ofxRangeSensorBlob blob;
    blob.color = ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
    return blob;
}




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
            if(data[index]>0.9){
                ofSetColor(255);
            }else{
                ofSetColor(100);
            }
            ofEllipse(xx*gridW, yy*gridH, 0.02, 0.02);
        }
    }
}


void ofxRangeSensorManager::drawSensor(ofxRangeSensor *sensor){
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
    }
    
    //Draw Sensor
    ofSetColor(255,255,0);
    ofEllipse(sensor->position.x, sensor->position.y,  0.05, 0.05);
}




