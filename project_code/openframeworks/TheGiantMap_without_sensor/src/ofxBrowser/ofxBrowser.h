//
//  ofxAwesomium.h
//  AwesomiumStudy
//
//  This add-on provides in-app chromium browser.
//  ofxBrowser and Awesomium.framework 1.72 is required.
//
//  Awesomium: http://www.awesomium.com/
//  Awesomium Class Reference: http://www.awesomium.com/docs/1_7_2/cpp_api/
//  Awesomium tutorial: http://wiki.awesomium.com/tutorials/tutorial-1-hello-awesomium.html
//  Created by Takayuki Fukatsu on 2014/02/21.
//
//

#pragma once

#ifndef __AwesomiumStudy__ofxAwesomium__
#define __AwesomiumStudy__ofxAwesomium__


#include "ofMain.h"
#include <iostream>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/WebKeyboardEvent.h>
#include <Awesomium/JSArray.h>
#include <Awesomium/JSObject.h>
#include <Awesomium/JSValue.h>

class ofxBrowser{
    public:
        void setup(int width, int height);
        void update();
        void draw();
        void tearDown();
        void loadURL(const char *str);
        void loadFile(const char *str);
    
        Awesomium::JSValue invokeJavaScript(const char *funcName);
        Awesomium::JSValue invokeJavaScript(const char *funcName, Awesomium::JSArray args);
    
        bool isLoading();
        int getWidth();
        int getHeight();
        ofTexture* getTexture();
    
        //Browser Interaction
        void mouseMoved(int x, int y);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseDragged(int x, int y, int button);
        void keyPressed(int key);
        void keyReleased(int key);
    private:
        Awesomium::WebView *webView;
        Awesomium::WebCore *webCore;
        int webViewWidth;
        int webViewHeight;
        ofTexture webTexture;
};

#endif /* defined(__AwesomiumStudy__ofxAwesomium__) */
