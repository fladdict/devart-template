#pragma once

#include "ofMain.h"
#include "urg_sensor.h"
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
private:
    int getXY(urg_t *urg, long *data);
    urg_t urg;
    long *data;
    long max_distance;
    long min_distance;
    std::vector<ofVec2f> points;
    
    long frame_count = 0;
};
