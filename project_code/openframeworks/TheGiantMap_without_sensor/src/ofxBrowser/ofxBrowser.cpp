//
//  ofxAwesomium.cpp
//  AwesomiumStudy
//
//  Created by 深津 貴之 on 2014/02/21.
//
//

#include "ofxBrowser.h"


void ofxBrowser::setup(int width, int height){
    webViewWidth = width;
    webViewHeight = height;
    webTexture.allocate(webViewWidth, webViewHeight, GL_RGB);
    webCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
    webView = webCore->CreateWebView(webViewWidth, webViewHeight);
    webView->Focus();
}


void ofxBrowser::update(){
    webCore->Update();
    
    /*
     //Create Texture
     //  http://www.awesomium.com/docs/1_7_2/cpp_api/class_awesomium_1_1_bitmap_surface.html
     */
    Awesomium::BitmapSurface *surface = (Awesomium::BitmapSurface*)webView->surface();
    if(surface){
        webTexture.loadData(surface->buffer(), surface->width(), surface->height(), GL_BGRA);
    }
}


void ofxBrowser::draw(){
    webTexture.draw(0,0, webViewWidth, webViewHeight);
}


void ofxBrowser::tearDown(){
    webTexture.clear();
    webView->Destroy();
    Awesomium::WebCore::Shutdown();
}



#pragma mark -

void ofxBrowser::loadURL(const char *str){
    Awesomium::WebURL url(Awesomium::WSLit(str));
    webView->LoadURL(url);
}


void ofxBrowser::loadFile(const char *str){
    loadURL(str);
}

Awesomium::JSValue ofxBrowser::invokeJavaScript(const char *funcName){
    Awesomium::JSArray ar;
    return invokeJavaScript(funcName, ar);
}

Awesomium::JSValue ofxBrowser::invokeJavaScript(const char *funcName, Awesomium::JSArray args){
    Awesomium::JSValue window = webView->ExecuteJavascriptWithResult(Awesomium::WSLit("window"),Awesomium::WSLit(""));
    if(window.IsObject()){
        Awesomium::JSValue value =  window.ToObject().Invoke(Awesomium::WSLit(funcName), args);
        return value;
    }
    return;
}



#pragma mark - Getter

bool ofxBrowser::isLoading(){
    return webView->IsLoading();
}


int ofxBrowser::getWidth(){
    return webViewWidth;
}


int ofxBrowser::getHeight(){
    return webViewHeight;
}


ofTexture* ofxBrowser::getTexture(){
    return &webTexture;
}


#pragma mark - Browser Control Delegation


void ofxBrowser::mouseMoved(int x, int y){
    webView->InjectMouseMove(x, y);
}


void ofxBrowser::mousePressed(int x, int y, int button){
    if(button==0){
        webView->InjectMouseDown(Awesomium::kMouseButton_Left);
    }else{
        webView->InjectMouseDown(Awesomium::kMouseButton_Right);
    }
}


void ofxBrowser::mouseReleased(int x, int y, int button){
    if(button==0){
        webView->InjectMouseUp(Awesomium::kMouseButton_Left);
    }else{
        webView->InjectMouseUp(Awesomium::kMouseButton_Right);
    }
}


void ofxBrowser::mouseDragged(int x, int y, int button){
    webView->InjectMouseMove(x, y);
}


void ofxBrowser::keyPressed(int key){
    //Character input only
    Awesomium::WebKeyboardEvent keyEvent;
    keyEvent.type = Awesomium::WebKeyboardEvent::kTypeChar;
    keyEvent.text[0] = key;
    keyEvent.unmodified_text[0] = key;
    keyEvent.virtual_key_code = key;
    keyEvent.native_key_code = key;
    webView->InjectKeyboardEvent(keyEvent);
}


void ofxBrowser::keyReleased(int key){
}


