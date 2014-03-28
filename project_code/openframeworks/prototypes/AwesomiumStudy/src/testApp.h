#pragma once

#include "ofMain.h"
#include "ofxBrowser.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>


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
    
        ofxBrowser browser;
    
    ofFilePath filePath;
    Awesomium::WebView *webView;
    Awesomium::WebCore *webCore;
    Awesomium::WebSession *webSession;
    int webTexWidth;
    int webTexHeight;
    ofTexture webTex;
};
