#include "ofApp.h"
/*
 In OpenGL Y is Up
 */
int currentScene = 0;
//--------------------------------------------------------------
void ofApp::setup()
{
    voxelGridScene      = new VoxelGridScene();
    testDerivedScene    = new TestDerivedScene();
    
    voxelGridScene->setup();
    testDerivedScene->setup();
    
}

//--------------------------------------------------------------
void ofApp::update()
{
    switch(currentScene)
    {
    case 49:
        voxelGridScene->update();
        break;
    case 50:
        testDerivedScene->update();
        break;
    default:
        voxelGridScene->update();
        break;
    };
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    switch(currentScene)
    {
    case 49:
        voxelGridScene->draw();
        break;
    case 50:
        testDerivedScene->draw();
        break;
    default:
        voxelGridScene->draw();
        break;
    };

}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete voxelGridScene;
    delete testDerivedScene;

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //voxelGridScene->keyPressed(key);
    switch(currentScene)
    {
    case 49: //1
        voxelGridScene->keyPressed(key);
        break;
    case 50: //2
        testDerivedScene->keyPressed(key);
        break;
    default:
        voxelGridScene->keyPressed(key);
        break;
    };
    currentScene = key;
    //std::cout<< key<<" Change to default Scene\n";
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
