#include "testApp.h"

using namespace Awesomium;

#define URL     "http://labs.theguild.jp/thegiantmap/map/index.html"



//--------------------------------------------------------------
void testApp::setup(){
    browser.setup(1024, 768);
    browser.loadURL("http://openframeworks.cc");
    
   
    
    /*
    //Setup Texture
    webTexWidth = ofGetWindowWidth();
    webTexHeight = ofGetWindowHeight();
    webTex.allocate(1024, 768, GL_RGB);
    
    //Setup WebCore
    WebConfig config;
    webCore = WebCore::Initialize(config);
    
    //Setup WebView
    webView = webCore->CreateWebView(webTexWidth, webTexHeight);
    WebURL url(WSLit(URL)); //Needs <Awesomium/STLHelpers.h> header to work.
    webView->LoadURL(url);
    
    //webView->Focus();
    cout << "Start loading.." << endl;
    while (webView->IsLoading()){
        webCore->Update();
    }
    cout << "Loaded" << endl;
    */
}

void testApp::exit(){
    browser.tearDown();
    
    /*
    // Destroy our WebView instance
    webView->Destroy();
    WebCore::Shutdown();
    */
}


//--------------------------------------------------------------
void testApp::update(){
    
    browser.update();
    
    /*
    webCore->Update();
    BitmapSurface *surface = (BitmapSurface*)webView->surface();
    if(surface!=0){
        webTex.loadData(surface->buffer(), surface->width(), surface->height(), GL_BGRA);
        
        cout << "W: " << surface->width() << endl;
        cout << "H: " << surface->height() << endl;
        cout << "row_span: " << surface->row_span() <<endl;
    }*/
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
    browser.draw();
    //webTex.draw(0,0, webTexWidth, webTexHeight);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    browser.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    browser.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    browser.mouseMoved(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    browser.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    browser.mousePressed(x, y, button);
    //webView->InjectMouseDown(kMouseButton_Left);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    browser.mouseReleased(x, y, button);
    //dwebView->InjectMouseUp(kMouseButton_Left);
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
