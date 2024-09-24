#include "ofApp.h"
/*
 In OpenGL Y is Up
 */
//--------------------------------------------------------------
void ofApp::setup()
{
    voxelGridScene = new VoxelGridScene();
    voxelGridScene->setup();
}

//--------------------------------------------------------------
void ofApp::update()
{
    voxelGridScene->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    voxelGridScene->draw();

}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete voxelGridScene;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    voxelGridScene->keyPressed(key);
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
