#include "testApp.h"

#include "urg_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//--------------------------------------------------------------
void testApp::setup(){
    const char connect_address[] = "192.168.0.10";
	const long connect_port = 10940;
    
    
    
    if(urg_open(&urg, URG_ETHERNET, connect_address, connect_port) < 0) {
        fprintf(stderr, "failed to open URG.\n");
        return;
    }
    
    data = (long *)malloc(urg_max_data_size(&urg) * sizeof(data[0]));
    if (!data) {
        perror("urg_max_index()");
        return;
    }
    
    //urg_reboot(&urg);
    
    urg_start_measurement(&urg, URG_DISTANCE, 0, 0);
    
    ofBackground(0, 0, 0);
    
    ofSleepMillis(1000);
}


int testApp::getXY(urg_t *urg, long *data) {
    long time_stamp;
    
    int n = urg_get_distance(urg, data, &time_stamp);
    
    if(n < 0) {
        if (n < 0) {
            printf("urg_get_distance: %s\n", urg_error(urg));
            //urg_close(urg);
            return 1;
        }
    }
    
    urg_distance_min_max(urg, &min_distance, &max_distance);
    printf("min = %ld mm, max = %ld mm\n", min_distance, max_distance);
    for(int i = 0; i< n; i++) {
        long distance = data[i];
        double radian;
        long x, y;
        
        if((distance < min_distance) || (distance > max_distance)) {
            continue;
        }
        
        radian = urg_index2rad(urg, i);
        x = (long)(distance * cos(radian));
        y = (long)(distance * sin(radian));
        
        ofVec2f p((float)x, (float)y);
        
        points.push_back(p);
        
        printf("%ld, %ld\n", x, y);
    }
    printf("\n");
    
    return 0;
}

//--------------------------------------------------------------
void testApp::update(){
    cout << "Status: " << urg_sensor_status(&urg) << endl;
    cout << urg_is_stable(&urg) << endl;
    
    //if(urg_is_stable(&urg)){
        if(getXY(&urg, data) != 0) {
            fprintf(stderr, "failed to fetch x and y coordinates.\n");
            points.clear();
            return;
        }
    //}
}

//--------------------------------------------------------------
void testApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    ofSetColor(255, 255, 255);
    for(int i=0; i<points.size(); i++) {
        float x = (float)points[i].x/max_distance * width;
        float y = (float)points[i].y/max_distance * height;
        ofCircle(x, y, 2.0);
    }
    points.clear();
}

void testApp::exit() {
    urg_stop_measurement(&urg);
    urg_close(&urg);
    free(data);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}
