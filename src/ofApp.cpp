#include "ofApp.h"
/*
 In OpenGL Y is Up
 */
int currentScene = 52;
//--------------------------------------------------------------
void ofApp::setup()
{
    voxelGridScene          = new VoxelGridScene();
    //testDerivedScene        = new TestDerivedScene();
    rayIntersectionScene    = new RayIntersectionScene();
    boidsNaiveScene         = new BoidsNaiveScene();
    sensingBoidsScene       = new SensingBoidsScene("Boids with Rays");
    
    voxelGridScene->setup();
    //testDerivedScene->setup();
    rayIntersectionScene->setup();
    boidsNaiveScene->setup();
    sensingBoidsScene->setup();
    
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
        rayIntersectionScene->update();
        break;
    case 51:
        boidsNaiveScene->update();
        break;
    case 52:
        sensingBoidsScene->update();
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
        rayIntersectionScene->draw();
        break;
    case 51:
        boidsNaiveScene->draw();
        break;
    case 52:
        sensingBoidsScene->draw();
        break;
    };

}

//--------------------------------------------------------------
void ofApp::exit()
{
    delete voxelGridScene;
    delete rayIntersectionScene;
    delete boidsNaiveScene;
    delete sensingBoidsScene;

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //std::cout << key << '\n';
    //voxelGridScene->keyPressed(key);
    
    switch(key)
    {
    case 49: //1
        currentScene = key;
        break;
    case 50: //2
        currentScene = key;
        break;
    case 51: //3
            currentScene = key;
        break;
    case 52: //4
            currentScene = key;
        break;
    };
    
    switch(currentScene)
    {
    case 49: //1
        voxelGridScene->keyPressed(key);
        break;
    case 50: //2
        rayIntersectionScene->keyPressed(key);
        break;
    case 51:
        boidsNaiveScene->keyPressed(key);
        break;
    case 53:
        sensingBoidsScene->keyPressed(key);
        break;
    };
    //currentScene = key == 49 || key == 50 ? 49 :;
    
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
