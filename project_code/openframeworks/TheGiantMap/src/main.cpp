#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
    //We user shader ver 1.2 so no ProgramabbleRenderer
    //ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);

	ofSetupOpenGL(800,800,OF_WINDOW);			// <-------- setup the GL context
    //ofSetupOpenGL(1024*2,768*2,OF_WINDOW);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
