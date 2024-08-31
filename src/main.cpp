#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    std::cout << "Hello in main" << '\n';
    
	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
	settings.setSize(1270, 780);//1024, 768
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
    settings.title = "Spatial partitioning";
	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
