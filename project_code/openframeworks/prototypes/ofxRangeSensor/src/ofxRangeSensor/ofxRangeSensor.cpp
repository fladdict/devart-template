//
//  ofxRangeSensor.cpp
//  ofxRangeSensor
//
//  Created by 深津 貴之 on 2014/02/28.
//
//

#include "ofxRangeSensor.h"
#include "urg_utils.h"
#include <string.h>

ofxRangeSensor::ofxRangeSensor(){
    for(int i=0; i<scanStep; i++){
        float angle = i * scanAngle / (float)scanStep;
    }
}



void ofxRangeSensor::setup(char address[], long port){
    strcpy(connect_address, address);
    connect_port = port;
}



void ofxRangeSensor::update(){
    if(!isOpen){
        return;
    }
    
    /*
    cout << "----------------" << endl;
    cout << "state: " << urg_sensor_state(&urg) << endl;
    cout << "stateus: " << urg_sensor_status(&urg) << endl;
    cout << "stability: " << urg_is_stable(&urg) << endl;
     */

    start();    //Needs Every frame
    long time_stamp;    //stored last time stamp
    int n = urg_get_distance(&urg, tempData, &time_stamp);  //Data is returend by milli metor
    stop(); //Nees Every frame
    
    
    if(n>0){
        memmove(&tempData, &data, sizeof(data));
    }else{
        //
    }
}


/*
 ------------------------------------
 URG Manipulation
 ------------------------------------
 */

void ofxRangeSensor::open(){
    if(urg_open(&urg, URG_ETHERNET, connect_address, connect_port)!=0){
        cout << "URG: " << urg_error(&urg) << endl;
        return;
    }
    
    isOpen = true;
    
    scanStep = dataSize = urg_max_data_size(&urg);
    tempData = (long *)malloc(dataSize * sizeof(long));
    data = (long *)malloc(dataSize * sizeof(long));
    urg_distance_min_max(&urg, &minDistance, &maxDistance);
    urg_step_min_max(&urg, &minStep, &maxStep);
    
    scanStep = abs(minStep) + maxStep + 1;
    
    cout << "URG opended: " << connect_address << endl;
    cout << "Serial: " << urg_sensor_serial_id(&urg) << endl;
    cout << "Data Size: " << dataSize << endl;
    cout << "Min Distance: " << minDistance << endl;
    cout << "Max Distance: " << maxDistance << endl;
    cout << "Min Step: " << minStep << endl;
    cout << "Max Step: " << maxStep << endl;
}



void ofxRangeSensor::close(){
    if(!isOpen){
        return;
    }
    
    urg_close(&urg);
    free(tempData);
    free(data);
    isOpen = false;
    cout << "URG closed" << endl;
}



void ofxRangeSensor::start(){
    if(!isOpen){
        cout << "Error: URG is not open yet" << endl;
        return;
    }
    
    if(urg_start_measurement(&urg, URG_DISTANCE, 0, 0)!=0){
        cout << urg_error(&urg) << endl;
        return;
    }

    isStart = true;
}



void ofxRangeSensor::stop(){
    if(urg_stop_measurement(&urg)!=0){
        //cout << "URG: stop failed. " << urg_error(&urg) << endl;
        return;
    };
    
    isStart = false;
    //cout << "URG: stopped" << endl;
}

/*----------------------------------------
 Utils
 ----------------------------------------*/
float ofxRangeSensor::stepToAngle(int step){
    return ofMap(float(step), 0, scanStep, 135, -135);
}

float ofxRangeSensor::stepToRadian(int step){
    return stepToAngle(step) * M_PI / 180.0;
}

float ofxRangeSensor::stepToGlobalAngle(int step){
    return stepToAngle(step) + rotation;
}

float ofxRangeSensor::stepToGlobalRadian(int step){
    return stepToGlobalAngle(step) * M_PI / 180.0;
}



