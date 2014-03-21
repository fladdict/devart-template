#include "testApp.h"
#include "ofxGui.h"
#include "Node.h"
#include "SmokeEmitter.h"
#include "AirPlane.h"
#include "ofEvents.h"
#include "CrackParticleEmitter.h"
#include "FloorSystemSwitch.h"
#include "FloorSystemRangeSensor.h"


bool isDebugMode;
Node nodes[100][100];

float mouseX;
float mouseY;
float mpx;
float mpy;
float mx;
float my;

SmokeEmitter smokeEmitter;
AirPlane airPlane;
Cloud cloud;
ofPlanePrimitive plane;

//Crack
CrackParticleEmitter crackEmitter;





#pragma mark - Setup

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    isDebugMode = false;
    
    
    /*********************************************
     Setup Particles
     *********************************************/
    smokeEmitter.setup();
    crackEmitter.setup();
    airPlane.setup();
    cloud.setup();
    
    /*********************************************
     Setup Mesh
     *********************************************/
    //Setup Mesh
    gridNodeColNum = (ofGetWidth() / GRID_WIDTH +1) + NUM_GRID_NODE_COL_MARGIN*2;
    gridNodeRowNum = (ofGetHeight() / GRID_HEIGHT +1) + NUM_GRID_NODE_ROW_MARGIN*2;
    fboWidth = ofGetWidth() + GRID_WIDTH * NUM_GRID_NODE_COL_MARGIN * 2;
    fboHeight = ofGetHeight() + GRID_HEIGHT * NUM_GRID_NODE_ROW_MARGIN * 2;
    fboOffsetX = GRID_WIDTH * NUM_GRID_NODE_COL_MARGIN;
    fboOffsetY = GRID_HEIGHT * NUM_GRID_NODE_ROW_MARGIN;
    
    
    for(int y=0; y<gridNodeRowNum; y++){
        for(int x=0; x<gridNodeColNum; x++){
            Node nd;
            nd.x = nd.initialX = GRID_WIDTH * (x - NUM_GRID_NODE_COL_MARGIN);
            nd.y = nd.initialY = GRID_HEIGHT * (y - NUM_GRID_NODE_ROW_MARGIN);
            nodes[y][x] = nd;
        }
    }
    
    locationIndex = 0;
    locations[0].lat = 51.5148028;
    locations[0].lng = -0.0938382;
    locations[0].zoom = 14;
    locations[0].title = "Barbican Center";
    locations[0].country = "United Kingdom";
    
    
    locations[1].lat = 37.4522731;
    locations[1].lng = -122.0687178;
    locations[1].zoom = 13;
    locations[1].title = "Google";
    locations[1].country = "USA";
    
    locations[2].lat = 35.65857;
    locations[2].lng = 139.7455032;
    locations[2].zoom = 14;
    locations[2].title = "Tokyo Tower";
    locations[2].country = "Japan";
    
    locations[3].lat = 41.8871992;
    locations[3].lng = 12.4899848;
    locations[3].zoom = 13;
    locations[3].title = "Colosseo";
    locations[3].country = "Italia";
    
    locations[4].lat = 32.1520709;
    locations[4].lng = -110.828005;
    locations[4].zoom = 16;
    locations[4].title = "Airplane Graveyard";
    locations[4].country = "USA";
    
    locations[5].lat = -44.1148559;
    locations[5].lng = 171.254887;
    locations[5].zoom = 13;
    locations[5].title = "Geraldine7";
    locations[5].country = "Newzealand";
    
    locations[6].lat = 27.1722869;
    locations[6].lng = 78.0420885;
    locations[6].zoom = 10;
    locations[6].title = "Taj Mahal";
    locations[6].country = "India";
    
    locations[7].lat = 48.8474121;
    locations[7].lng = 2.3958026;
    locations[7].zoom = 13;
    locations[7].title = "Place de la Nation";
    locations[7].country = "France";
    
    
    /*********************************************
     Setup Floor Manager
     *********************************************/
    //ofPtr<FloorSystemSwitch> fs(new FloorSystemSwitch());
    ofPtr<FloorSystemRangeSensor> fsr(new FloorSystemRangeSensor());
    fsr->setup("/dev/tty.usbmodem1421", 9600);
    floorSystem = fsr;
    ofAddListener(floorSystem->floorTouched, this, &testApp::onFloorTouched);
    
    
    
    /*********************************************
     Setup Shader
     *********************************************/
    plane.set(fboWidth, fboHeight, 2, 2);
    plane.mapTexCoords(0, 0, fboWidth, fboHeight);
    

    lookupImage0.loadImage("lookups/lut-sunrise.png");
    lookupImage1.loadImage("lookups/lut-daylight.png");
    lookupImage2.loadImage("lookups/lut-sunset.png");
    lookupImage3.loadImage("lookups/lut-evening.png");
    lookupImages.push_back(lookupImage0);   //0: Morning
    lookupImages.push_back(lookupImage1);
    lookupImages.push_back(lookupImage1);
    lookupImages.push_back(lookupImage1);
    lookupImages.push_back(lookupImage1);
    lookupImages.push_back(lookupImage1);
    lookupImages.push_back(lookupImage2);   //6: Evening
    lookupImages.push_back(lookupImage3);   //7: Night
    lookupImages.push_back(lookupImage3);
    lookupImages.push_back(lookupImage3);
    lookupImages.push_back(lookupImage0);   //10: Morning
    shader.load("shaders/simpleVertex.vert", "shaders/multiLookupFilter.frag");
    
    nightShader.setup(fboWidth, fboHeight);
    transitionShader.load("shaders/simpleVertex.vert", "shaders/video.frag");
    
    
    /*********************************************
     Setup Initial Screen
     *********************************************/
    shaderFbo.allocate(fboWidth, fboHeight);
    mapFbo.allocate(fboWidth, fboHeight);
    lutFbo.allocate(fboWidth, fboHeight);
    destFbo.allocate(fboWidth, fboHeight);
    

    /*********************************************
     Setup Other Tools
     *********************************************/
    setupSyphon();
    setupGui();
    soundManager.setup();
    
    /*********************************************
     Setup Browser
     *********************************************/
    browser.setup(fboWidth, fboHeight);
    browser.loadURL("http://labs.theguild.jp/thegiantmap/map/");
}


void testApp::setupSyphon(){
    mainOutputSyphonServer.setName("Screen Outputh");
    mClient.setup();
    mClient.setApplicationName("Simple Serverh");
    mClient.setServerName("");
}




void testApp::setupGui(){
    guiEnabled = false;
    
    ofParameter<string> paramLabel0;
    ofParameter<string> paramLabel1;
    ofParameter<string> paramLabel2;
    ofParameter<string> paramLabel3;
    ofParameter<string> paramLabel4;
    ofParameter<string> paramLabelSplitter;
    
    gui.setup("panel");
    gui.add(paramLabel0.set("Grid Physics"));
    gui.add(paramNodeFriction.set("Node Friction", 0.95, 0, 1));
    gui.add(paramNodeShakeFriction.set("Node ShakeFriction", 0.95, 0, 1));
    gui.add(paramSpringK.set("Spring K", 0.1, 0, 1));
    gui.add(paramIsMouseMoveShake.set("Mouse Move Shake", true));
    
    
    gui.add(paramLabelSplitter.set(""));
    gui.add(paramLabel1.set("Giant Step"));
    gui.add(paramGiantStepForceAmplifier.set("Step Force",280,0,500));
    gui.add(paramGiantStepForceClamp.set("Force Clamp",12,0,100));
    gui.add(paramGiantStepShakeForceAmplifier.set("Shake Force",500,0,1000));
    gui.add(paramGiantStepShakeForceClamp.set("Shake Force Clamp",10,0,100));
    
    gui.add(paramLabelSplitter.set(""));
    gui.add(paramLabel2.set("Grid Lines"));
    gui.add(paramIsDrawLines.set("Lines Visible", false));
    gui.add(paramLineMinBrightness.set("Lines Brightness MIN", 50, 0, 255));
    gui.add(paramLineMaxBrightness.set("Lines Brightness MAX", 75, 0, 255));
    
    gui.add(paramLabelSplitter.set(""));
    gui.add(paramLabel3.set("Shader"));
    gui.add(paramShaderInterpolation.set("Interpolation", 0.00, 0.00, lookupImages.size()-1));
    gui.add(paramShaderInterpolationVelocity.set("Interpolation", 0.005, 0.00, 0.05));
    gui.add(paramHazeAlpha.set("Haze Alpha", 0.0, 0.00, 255.0));
    gui.add(paramAutoTransitionProbability.set("Auto Location Move",0.25,0.00,1.00));
    
    gui.add(paramLabelSplitter.set(""));
    gui.add(paramLabel4.set("Browser"));
    gui.add(paramIsBrowserMode.set("Browser Control Mode", false));
    gui.add(paramIsWireframeMode.set("Wireframe Mode", false));
}


void testApp::exit(){
    browser.tearDown();
}


#pragma mark - Update


//--------------------------------------------------------------
void testApp::update(){
    floorSystem->update();
    browser.update();
    
    paramShaderInterpolation+= paramShaderInterpolationVelocity;
    if(paramShaderInterpolation>lookupImages.size()-1){
        paramShaderInterpolation = 0;
    }
    
    if(paramIsMouseMoveShake){
        //Apply mouse effect
        for(int y=0; y<gridNodeRowNum; y++){
            for(int x=0; x<gridNodeColNum; x++){
                Node *nd = &nodes[y][x];
                float dx = nd->x - mouseX;
                float dy = nd->y - mouseY;
                float dist = sqrt(dx*dx+dy*dy);
                if(dist>5){
                    float d = pow(dist, 1.75f);
                    float fx = dx / d* 80;
                    float fy = dy / d* 80;
                    fx = ofClamp(fx, -2, 2);
                    fy = ofClamp(fy, -2, 2);
                    nd->vx -= fx;
                    nd->vy -= fy;
                }
            }
        }
    }
    
    for(int y=0; y<gridNodeRowNum; y++){
        for(int x=0; x<gridNodeColNum; x++){
            Node *nd = &nodes[y][x];
            
            float dx = nd->initialX - nd->x;
            float dy = nd->initialY - nd->y;
            nd->vx += dx * paramSpringK;
            nd->vy += dy * paramSpringK;
            nd->vx *= paramNodeFriction;
            nd->vy *= paramNodeFriction;
            nd->x += nd->vx;
            nd->y += nd->vy;
            nd->shakeCount *= paramNodeShakeFriction;
            nd->shake.x = ofRandom(-1, 1) * nd->shakeCount;
            nd->shake.y = ofRandom(-1, 1) * nd->shakeCount;
        }
    }
    
    //Update Particles
    smokeEmitter.update();
    crackEmitter.update();
    sparkEmitter.update();
    if(hazeEmitter.alpha>0.01){
        hazeEmitter.update();
        if(ofRandom(0,1)<0.2){
            hazeEmitter.addParticles(0, 0, 3);
        }
    }
    hazeEmitter.tAlpha = paramHazeAlpha;
    airPlane.update();
    cloud.update();
}



#pragma mark - Draw

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(ofColor::white);
    ofSetColor(ofColor::white);
    
    
    //Update Dest Fbo
    mapFbo.begin();
    ofPushMatrix();
    ofEnableAlphaBlending();
    browser.draw();
    ofTranslate(GRID_WIDTH*NUM_GRID_NODE_COL_MARGIN, GRID_HEIGHT*NUM_GRID_NODE_ROW_MARGIN);
    crackEmitter.draw();
    ofDisableAlphaBlending();
    ofPopMatrix();
    mapFbo.end();

    
    /*
     ----------------------------------------------
     Draw destination texture
     ----------------------------------------------
     */
    
    if(paramIsWireframeMode){
        ofBackground(ofColor::black);
        ofSetColor(ofColor::white);
        drawLines();
        if(guiEnabled){
            gui.draw();
        }
        mClient.draw(50,50);
        mainOutputSyphonServer.publishScreen();
        return;
    }
    
    shaderFbo.begin();
        ofPushMatrix();
        drawMesh();
        drawLines();
    
        cloud.draw();
        if(hazeEmitter.alpha>0.01){
            hazeEmitter.draw();
        }
        smokeEmitter.draw();
        sparkEmitter.draw();
    
        airPlane.draw();
        ofPopMatrix();
    shaderFbo.end();
    
    /*
     ----------------------------------------------
     Apply Lookup Shader
     ----------------------------------------------
     */
    
    int index0 = (int)floor(paramShaderInterpolation);
    int index1 = (int)ceil(paramShaderInterpolation);
    float interpolation = paramShaderInterpolation - floor(paramShaderInterpolation);
    
    //cout << index0 << " " << index1 << " " << interpolation << endl;
    
    lutFbo.begin();
    shader.begin();
        ofPushMatrix();
        shader.setUniformTexture("sourceTexture", shaderFbo.getTextureReference(), 1);
        shader.setUniformTexture("lookupTexture0", lookupImages[index0].getTextureReference(), 2);
        shader.setUniformTexture("lookupTexture1", lookupImages[index1].getTextureReference(), 3);
        shader.setUniform1f("interpolation", interpolation);
        ofTranslate(fboWidth*0.5, fboHeight*0.5);
        plane.draw();
        ofPopMatrix();
    shader.end();
    lutFbo.end();
    
    
    
    /*
     ----------------------------------------------
     Apply Night Shader
     ----------------------------------------------
     */
    float nightOverlayAlpha;
    if(paramShaderInterpolation<2){
        nightOverlayAlpha = 0;
        paramHazeAlpha = ofClamp(paramHazeAlpha*=0.95, 0, 255);
        
        if(paramShaderInterpolation>1 && paramShaderInterpolation-paramShaderInterpolationVelocity<1){
            if(ofRandom(0,1)<paramAutoTransitionProbability){
                setRandomLocation();
            }
        }
    }if(paramShaderInterpolation<6){
        nightOverlayAlpha = 0;
    }else if(paramShaderInterpolation<7){
        //Evening to Night
        nightOverlayAlpha = paramShaderInterpolation - 6;
    }else if(paramShaderInterpolation<9) {
        //Night
        paramHazeAlpha = 0;
        nightOverlayAlpha = 1.0;
    }else if(paramShaderInterpolation<9.5){
        //Night to Morning
        
        nightOverlayAlpha = 1-(paramShaderInterpolation-9)*2;
        
        if(paramShaderInterpolation>9 && paramShaderInterpolation-paramShaderInterpolationVelocity<9){
            //haze only exists morning and 10%
            paramHazeAlpha = ofRandom(100,255);
        }
    }else{
        nightOverlayAlpha = 0;
    }
    
    nightShader.overlayAlpha = nightOverlayAlpha*0.5;  //Constrain this for only work on night time.
    nightShader.applyEffect(&lutFbo, &destFbo);
    
    
    
    
    /*
     ------------------------------
     Final render and transition_/_.
     ------------------------------
     */
    ofSetColor(ofColor::white);
    transitionCount *= 0.8;
    if(transitionCount>0.1){
        transitionShader.begin();
        transitionShader.setUniform1f("redOffsetX",   ofRandom(-1,1)*transitionCount * transitionCount);
        transitionShader.setUniform1f("redOffsetY",   ofRandom(-1,1)*transitionCount * transitionCount);
        transitionShader.setUniform1f("greenOffsetX", ofRandom(-1,1)*transitionCount * transitionCount);
        transitionShader.setUniform1f("greenffsetY",  ofRandom(-1,1)*transitionCount * transitionCount);
        transitionShader.setUniform1f("blueOffsetX",  ofRandom(-1,1)*transitionCount);
        transitionShader.setUniform1f("blueOffsetY",  ofRandom(-1,1)*transitionCount);
        destFbo.draw(0,0);
        transitionShader.end();
    }else{
        destFbo.draw(0,0);
    }
    
    
    if(guiEnabled){
        gui.draw();
    }
    
    //Syphon
    mClient.draw(50,50);
    mainOutputSyphonServer.publishScreen();
}


void testApp::drawMesh(){
    for(int y=0; y<gridNodeRowNum-1; y++){
        mapMesh.clear();
        mapMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        mapMesh.enableTextures();
        mapFbo.getTextureReference().bind();
        for(int x=0; x<gridNodeColNum; x++){
            Node *nd0 = &nodes[y][x];
            Node *nd1 = &nodes[y+1][x];
            
            mapMesh.addVertex(ofVec3f(nd0->x + nd0->shake.x, nd0->y + nd0->shake.y, 0));
            mapMesh.addVertex(ofVec3f(nd1->x + nd1->shake.x, nd1->y + nd1->shake.y, 0));
            mapMesh.addTexCoord(ofVec2f(x * GRID_WIDTH, y*GRID_HEIGHT));
            mapMesh.addTexCoord(ofVec2f(x * GRID_WIDTH, (y+1)*GRID_HEIGHT));
        }
        mapMesh.draw();
        mapFbo.getTextureReference().unbind();
    }
}


void testApp::drawLines(){
    if(!paramIsDrawLines && !paramIsWireframeMode)
        return;
    
    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    for(int y=0; y<gridNodeRowNum-1; y++){
        for(int x=0; x<gridNodeColNum-1; x++){
            Node *nd0 = &nodes[y][x];
            Node *nd1 = &nodes[y][x+1];
            Node *nd2 = &nodes[y+1][x];
            
            float dx0 = nd0->x - nd1->x;
            float dy0 = nd0->y - nd1->y;
            float dx1 = nd0->x - nd2->x;
            float dy1 = nd0->y - nd2->y;
            float dist0 = sqrt(dx0*dx0 + dy0*dy0);
            float dist1 = sqrt(dx1*dx1 + dy1*dy1);
            ofSetColor(255, 255-dist0*3, 255-dist0*3);
            ofLine(nd0->x, nd0->y, nd1->x, nd1->y);
            ofSetColor(255, 255-dist1*3, 255-dist1*3);
            ofLine(nd0->x, nd0->y, nd2->x, nd2->y);
        }
    }
    ofDisableBlendMode();
}



#pragma mark - Interaction

void testApp::applyGinantStep(float mouseX, float mouseY)
{
    //Shock Force
    for(int y=0; y<gridNodeRowNum; y++){
        for(int x=0; x<gridNodeColNum; x++){
            Node *nd = &nodes[y][x];
            float dx = nd->x - mouseX;
            float dy = nd->y - mouseY;
            float dist = sqrt(dx*dx+dy*dy);
            if(dist>5){
                float d = pow(dist, 1.75f);
                float fx = dx / d* paramGiantStepForceAmplifier;
                float fy = dy / d* paramGiantStepForceAmplifier;
                fx = ofClamp(fx, -paramGiantStepForceClamp, paramGiantStepForceClamp);
                fy = ofClamp(fy, -paramGiantStepForceClamp, paramGiantStepForceClamp);
                nd->vx -= fx;
                nd->vy -= fy;
            }
        }
    }
    
    
    //Shake
    for(int y=0; y<gridNodeRowNum-1; y++){
        for(int x=0; x<gridNodeColNum-1; x++){
            Node *nd = &nodes[y][x];
            float dx = mouseX - nd->x;
            float dy = mouseY - nd->y;
            float dist = sqrt(dx*dx+dy*dy);
            float f = paramGiantStepShakeForceAmplifier / pow(dist,1.2f);
            f = ofClamp(f, 0, paramGiantStepShakeForceClamp);
            nd->shakeCount = ofClamp(f+nd->shakeCount,0,paramGiantStepShakeForceClamp);
        }
    }
    
    sparkEmitter.addParticles(mouseX, mouseY, 100);
    crackEmitter.addParticle(mouseX, mouseY);
    smokeEmitter.addParticles(mouseX, mouseY, 20);
    soundManager.playShakeSound();
    
    /*
    //airplane check
    ofVec2f dist = airPlane.position - ofVec2f(mouseX,mouseY);
    float d = dist.length();
    if(d<30){
        smokeEmitter.addParticle(airPlane.position.x, airPlane.position.y);
        airPlane.explode();
    }*/
}

void testApp::setRandomLocation(){
    int i;
    while(true){
        i = ofRandom(0, NUM_LOCATIONS);
        if(i!=locationIndex){
            break;
        }
    }
    setLocationById(i);
}

void testApp::setLocationById(int i){
    locationIndex = i;
    airPlane.resetPosition();
    setLocation(locations[i].lat, locations[i].lng, locations[i].zoom);
}

void testApp::setLocation(float lat, float lng, int zoom){
    transitionCount = 100;
    crackEmitter.removeAllParticles();
    smokeEmitter.removeAllParticles();
    airPlane.resetPosition();
    cloud.resetPosition();
    
    const Awesomium::JSValue v_lat = Awesomium::JSValue(lat);
    const Awesomium::JSValue v_lnd = Awesomium::JSValue(lng);
    const Awesomium::JSValue v_zoom = Awesomium::JSValue(zoom);
    Awesomium::JSArray args;
    args.Push(v_lat);
    args.Push(v_lnd);
    args.Push(v_zoom);
    browser.invokeJavaScript("setLocation", args);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //Toggle Debug Mode
    isDebugMode = !isDebugMode;
    string str;
    
    cout << "Key: " << key;
    
    switch (key) {
        case 9:
            //Enable / Disable GUI
            guiEnabled = !guiEnabled;
            break;
        case 49:
            //1
            //set Location To Barbican
            setLocationById(0);
            //setLocation(51.5148028, -0.0938382, 14);
            break;
        case 50:
            //2
            //set Location To Google CA
            setLocationById(1);
            break;
        case 51:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(2);
            break;
        case 52:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(3);
            break;
        case 53:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(4);
            break;
        case 54:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(5);
            break;
        case 55:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(6);
            break;
        case 56:
            //3
            //set Location to Japan Tokyo Tower
            setLocationById(7);
            break;
        case 99:
            //C: Capture
            saveImage();
        case 108:
            //L:
            gui.loadFromFile("settings.xml");
            //
            break;
        case 115:
            //s: Save
            gui.saveToFile("settings.xml");
            //saveImage();
            break;
        case 119:
            //W: Wireframe
            paramIsWireframeMode = !paramIsWireframeMode;
            break;
        case 59:
            //+
            airPlane.resetPosition();
            cloud.resetPosition();
            crackEmitter.removeAllParticles();
            str = "zoomIn";
            browser.invokeJavaScript(str.c_str());
            break;
        case 45:
            //-+
            airPlane.resetPosition();
            cloud.resetPosition();
            crackEmitter.removeAllParticles();
            str = "zoomOut";
            browser.invokeJavaScript(str.c_str());
            break;
        default:
            break;
    }
}


void testApp::saveImage(){
    ofImage img;
    img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    img.saveImage("capture.png");
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    mouseX = x;
    mouseY = y;
    if(paramIsBrowserMode){
        browser.mouseMoved(x, y);
    }
}


//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    mx = mpx = x;
    my = mpy = y;
    
    if(paramIsBrowserMode){
        browser.mousePressed(x, y, button);
    }else{
        applyGinantStep(x, y);
    }
}


void testApp::mouseReleased(int x, int y, int button){
    if(paramIsBrowserMode){
        browser.mouseReleased(x,y,button);
    }else{
    }
}

void testApp::mouseDragged(int x, int y, int button){
    
    mpx = mx;
    mpy = my;
    mx = x;
    my = y;
    
    if(paramIsBrowserMode){
        float dx = mx - mpx;
        float dy = my - mpy;
        
        crackEmitter.addPositionOffset(dx, dy);
        airPlane.addPositionOffset(dx, dy);
        cloud.addPositionOffset(dx, dy);
        browser.mouseDragged(x, y, button);
    }
}

void testApp::onFloorTouched(ofVec2f &e){
    float xx = (e.x*2+1) * ofGetHeight() / 6.0;
    float yy = (e.y*2+1) * ofGetHeight() / 6.0;
    cout << " " << xx << " " << yy << endl;
    applyGinantStep(yy, xx);
}
