#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"
#include "ofxSyphon.h"
#include "SoundManager.h"
#include "Cloud.h"
#include "NightShader.h"
#include "ofxBrowser.h"
#include "SparkEmitter.h"
#include "FloorSystemInterface.h"
#include "HazeEmitter.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 32
#define NUM_GRID_NODE_COL_MARGIN 2
#define NUM_GRID_NODE_ROW_MARGIN 2
#define NUM_LOCATIONS 8

struct Location{
    float lat;
    float lng;
    int zoom;
    string title;
    string country;
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseDragged(int x, int y, int button);
    private:
        //Arudino
        void drawMesh();
        void drawLines();
        void applyGinantStep(float x, float y);
        void setupSyphon();
        void setupGui();
        void setupArduino(const int & version);
        void updateArudino();
        void setRandomLocation();
        void setLocationById(int theId);
        void setLocation(float lat, float lng, int zoom);
        void saveImage();
        void onFloorTouched(ofVec2f &e);
    
    //Grid Definition
    int gridNodeColNum;
    int gridNodeRowNum;
    int fboWidth;
    int fboHeight;
    int fboOffsetX;
    int fboOffsetY;
    
    //Map
    int locationIndex;
    Location locations[NUM_LOCATIONS];
    ofMesh mapMesh;
    
    ofFbo mapFbo;
    ofFbo lutFbo;
    ofFbo destFbo;
    
    //GUI
    bool guiEnabled;
    ofxPanel gui;
    ofParameter<float> paramNodeFriction;
    ofParameter<float> paramNodeShakeFriction;
    ofParameter<float> paramSpringK;
    ofParameter<bool> paramIsMouseMoveShake;
    ofParameter<bool> paramIsDrawLines;
    ofParameter<int> paramLineMinBrightness;
    ofParameter<int> paramLineMaxBrightness;
    ofParameter<float> paramGiantStepForceAmplifier;
    ofParameter<float> paramGiantStepForceClamp;
    ofParameter<float> paramGiantStepShakeForceAmplifier;
    ofParameter<float> paramGiantStepShakeForceClamp;
    ofParameter<float> paramShaderInterpolation;
    ofParameter<float> paramShaderInterpolationVelocity;
    ofParameter<float> paramHazeAlpha;
    ofParameter<bool> paramIsBrowserMode;
    ofParameter<bool> paramIsWireframeMode;
    ofParameter<float> paramAutoTransitionProbability;
    
    //Syphon
    ofxSyphonServer mainOutputSyphonServer;
    ofxSyphonServer individualTextureSyphonServer;
    ofxSyphonClient mClient;
    
    //Shader
    ofFbo shaderFbo;
    vector<ofImage> lookupImages;
    ofImage lookupImage0;
    ofImage lookupImage1;
    ofImage lookupImage2;
    ofImage lookupImage3;
    ofShader shader;
    NightShader nightShader;
    float transitionCount;
    ofShader transitionShader;
    
    //Particles
    SparkEmitter sparkEmitter;
    HazeEmitter hazeEmitter;
    
    //Browser
    ofxBrowser browser;
    
    //SoundManager
    SoundManager soundManager;
    
    ofPtr<FloorSystemInterface> floorSystem;
};
