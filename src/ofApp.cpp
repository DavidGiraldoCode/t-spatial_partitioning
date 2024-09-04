#include "ofApp.h"


/*
 In OpenGL Y is Up
 */

//--------------------------------------------------------------
void ofApp::setup(){
    std::cout << "Hello in setup" << '\n';
    voxelGridResolution = 1;
    Messenger myMessenger = Messenger();
    
    std::cout << "Building the grid" << '\n';
    uniformGrid = UniformGrid(2,2,2, ofVec3f(0,0,0),ofVec3f(10,10,10));
    std::cout << "Grid size:" << uniformGrid.getGridSize() << '\n';
    
    ofEnableSmoothing();
    
    light.setup();
    light.setPosition(0, 500, 0);
    light.setAmbientColor(ofFloatColor(0.4, 1.0));
    // we set up a plane on which the truck will move
    plane.set(1000, 1000);
    //plane.rotateDeg(270, 1, 0 , 0);
    plane.rotateDeg(-90, glm::vec3{1,0,0});
    //plane.move(0, -49, 0);
    plane.setGlobalPosition(0, 0, 0);
    
    float width     = ofGetWidth() * .12;
    float height    = ofGetHeight() * .12;
    box.set( 1000/*width*1.25*/ );
    box.setGlobalPosition(0, box.getHeight()/2, 0);
    box.setResolution(1);
    

    ofFloatColor roadColor(0.7, 0.7);
    roadMaterial.setAmbientColor(roadColor);
    roadColor.a = 1.0;
    roadMaterial.setDiffuseColor(roadColor);
    roadMaterial.setShininess(0.01);

    //Set our camera up in a nice location to view our awesome car
    //-965, 586, -1084
    //cam.setPosition(-965,2000,-1000);
    
    cam.setGlobalPosition(0, 500, 1500);
    //cam.lookAt(truck.getNode(), {0.f, 1.f, 0.f});
    //cam.setNearClip(0);
    cam.setFarClip(10000);
    
    /*GUI*/

    gui.setup("Test settings"); // most of the time you don't need a name but don't forget to call setup
    gui.add(guiFramesPerSecond.set( "FPS", 1));
    gui.add(guiVoxelResolution.set( "Voxels", 1, 1, 100));
    gui.add(guiVoxelVisibility.set("Voxel visibility", true));
    //gui.add(center.set("center",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
    //gui.add(color.set("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    //gui.add(circleResolution.set("circleRes", 5, 3, 90));
    //gui.add(twoCircles.setup("twoCircles"));
    //gui.add(ringButton.setup("ring"));
    //gui.add(screenSize.set("screenSize", ""));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw a gradient in the background
    //ofBackgroundGradient(ofColor(10), ofColor(50));
    ofBackground(0, 0, 0);
    
    
    ofEnableDepthTest();
    cam.begin();
    
        roadMaterial.begin();
        //plane.draw();
        roadMaterial.end();
    
        plane.drawAxes(500);
        ofSetColor(50, 50, 50);
        box.drawWireframe();
        //ofSetColor(255, 100, 100);
        //box.drawNormals(10);
    
    
    ofDisableDepthTest();
    cam.end();
    
    
    
//    stringstream ss;
//    ss << "Spatial partitioning: " << '\n' << '\n';
//    ss << "FPS: " << ofToString(ofGetFrameRate(),0) << '\n' ;
//    ss << "Voxel Grid Resolution: " << voxelGridResolution << '\n' ;
//    ofDrawBitmapStringHighlight(ss.str().c_str(), 20, 20);
    
    /*GUI*/
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
