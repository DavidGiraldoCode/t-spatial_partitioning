#include "ofApp.h"


/*
 In OpenGL Y is Up
 */
//const int BOIDS_COUNT = 100;
//float VOXEL_SIZE = 200;
//--------------------------------------------------------------
void ofApp::setup(){
    voxelGridScene = new VoxelGridScene();
    voxelGridScene->setup();
    
    std::cout << "Hello in setup" << '\n';
    
    //Messenger myMessenger = Messenger();
    
    /* Custom Voxel*/
//    mesh.addVertex(ofVec3f(0,0,0));
//    mesh.addColor(ofColor::red);
//    mesh.addVertex(ofVec3f(100,0,0));
//    mesh.addColor(ofColor::red);
//    mesh.setMode(OF_PRIMITIVE_LINES);
//    mesh2 = mesh;
    
//    ofVec3f pointA = ofVec3f(0,0,0);
//    ofVec3f pointB = ofVec3f(100,0,0);
//    ofVec3f pointC = ofVec3f(0,100,0);
//    ofVec3f pointD = ofVec3f(100,100,0);
//    
//    ofVec3f pointE = ofVec3f(0,0,100);
//    ofVec3f pointF = ofVec3f(100,0,100);
//    ofVec3f pointG = ofVec3f(0,100,100);
//    ofVec3f pointI = ofVec3f(100,100,100);
//    
//    polyline.lineTo(pointA.x,pointA.y,pointA.z);
//    polyline.lineTo(pointB.x,pointB.y,pointB.z);
//    polyline.lineTo(pointD.x,pointD.y,pointD.z);
//    polyline.lineTo(pointC.x,pointC.y,pointC.z);
//    polyline.lineTo(pointA.x,pointA.y,pointA.z);
//    
//    polyline.lineTo(pointE.x,pointE.y,pointE.z);
//    polyline.lineTo(pointF.x,pointF.y,pointF.z);
//    polyline.lineTo(pointI.x,pointI.y,pointI.z);
//    polyline.lineTo(pointG.x,pointG.y,pointG.z);
//    polyline.lineTo(pointE.x,pointE.y,pointE.z);
//    
//    polyline.close();
    //ofVoxel
//    ofVoxel.set(100);
//    ofVoxel.setGlobalPosition(ofVoxel.getHeight()/2, ofVoxel.getHeight()/2, -ofVoxel.getHeight()/2);
//    ofVoxel.setResolution(1);
    
    //Set our camera up in a nice location to view our awesome car
    //-965, 586, -1084
    //cam.setPosition(-965,2000,-1000);
    
    
    
    /*Boid*/
    //boid = Boid(ofVec3f(box.getPosition()).x, ofVec3f(box.getPosition()).y, ofVec3f(box.getPosition()).z);
    //boidSphere.setGlobalPosition(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z);
    
    /*
    ofEnableSmoothing();
    
    //
    //CAMERA SETTINGS
    //
    cam.setGlobalPosition(1000, 1000, 2000);
    //cam.lookAt(truck.getNode(), {0.f, 1.f, 0.f});
    //cam.setNearClip(0);
    cam.setFarClip(10000);
    
    
    float width     = ofGetWidth() * .12;
    float height    = ofGetHeight() * .12;

    ofFloatColor roadColor(0.9,0.9,0.9,1);
    roadMaterial.setDiffuseColor(roadColor);
    //roadColor.a = 1.0;
    //roadMaterial.setDiffuseColor(roadColor);
    //roadMaterial.setShininess(0.01);
    
    //
    // GUI
    //

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
    gui.add(guiGridWidth.set( "Grid Width", 1, 1, 100));
    gui.add(guiGridHeight.set( "Grid Height", 1, 1, 100));
    gui.add(guiGridDepth.set( "Grid Depth", 1, 1, 100));

    // 
    //--------   Uniform grid
    //
    voxelGridResolution = 1;
    gridWidth = 10;
    gridHeight = 10;
    gridDepth = 15;
    
    
    //ofBox mesh that represets the bounding volume of the environmental obstacles
    box.set( gridWidth * VOXEL_SIZE, gridHeight * VOXEL_SIZE, gridDepth * VOXEL_SIZE);
    box.setGlobalPosition(box.getWidth()/2, box.getHeight()/2, box.getDepth()/2 * -1);
    box.setResolution(1);
    
    //ofQuad that represents the floor of the scene
    plane.set(gridWidth * VOXEL_SIZE, gridDepth * VOXEL_SIZE ,gridWidth, gridDepth);
    plane.rotateDeg(-90, glm::vec3{1,0,0});
    //plane.move(0, -49, 0);
    plane.setGlobalPosition(plane.getWidth()/2, 0, box.getDepth()/2 * -1);
    
    //I am removing the pivot argument to use the constructor that sets the grid at [0,0,0]
    uniformGrid = UniformGrid(gridWidth, gridHeight, gridDepth, /ofVec3f(0,0,0),/ VOXEL_SIZE);
    boidSphere.set(10, 16);
    std::cout << "Grid size:" << uniformGrid.getGridSize() << '\n';
    
    //ofPrimivite Sphere Mesh to represent the Boid
    ofVoxelB.set(VOXEL_SIZE);
    ofVoxelB.setGlobalPosition(ofVoxelB.getHeight()/2 + ofVoxel.getHeight(), ofVoxelB.getHeight()/2, -ofVoxelB.getHeight()/2);
    ofVoxelB.setResolution(1);
    
    ofFloatColor emptyColor(1,1,1,0.1);
    emptyVoxelMAT.setDiffuseColor(emptyColor);
    
    spatialQueryCursor.set(10,8);
    spatialQueryPosition = ofVec3f(0,0,0);
    
    spatialQueryCursor.setGlobalPosition(spatialQueryPosition.x, spatialQueryPosition.y, spatialQueryPosition.z);
    
    //Instantiating the Boids in the center of the bounding volume
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids.push_back(Boid(ofVec3f(box.getPosition()).x, ofVec3f(box.getPosition()).y, ofVec3f(box.getPosition()).z));
        boidSpheres.push_back(ofSpherePrimitive());
        boidSpheres[i].set(10, 16); //radius and resolution
    }
    
    //
    // LIGHT SETTINGS
    //
    
    light.setup();
    light.setPosition(box.getWidth()/2, box.getHeight(), box.getDepth()/2 * -1);
    light.setAmbientColor(ofFloatColor(0.4, 1.0));
    */
    
}
//bool isInside = false;
//--------------------------------------------------------------
void ofApp::update(){
    voxelGridScene->update();
    /*Custom Voxel*/
    //mesh.getVertices()[1].x+=0.1;
    //mesh2.getVertices()[1].x=mesh.getVertices()[1].x + 0.1;
    //boid.move();
    //boid.applyBoundingForce(ofVec3f(box.getPosition()), box.getWidth(), box.getHeight(), box.getDepth());
    //boidSphere.setGlobalPosition(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z);
    
    //voxelGridScene.update();
    /*
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids[i].applyBoundingForce(ofVec3f(box.getPosition()), box.getWidth(), box.getHeight(), box.getDepth());
        boids[i].move();
        boidSpheres[i].setGlobalPosition(boids[i].getPosition().x, boids[i].getPosition().y, boids[i].getPosition().z);
        
        boids[i].updatePositionInWorldGrid(uniformGrid);
        //isInside = uniformGrid.isPointInsideAVoxel(boids[i].getPosition());
    }
    
    
    
    spatialQueryCursor.setGlobalPosition(spatialQueryPosition.x, spatialQueryPosition.y, spatialQueryPosition.z);
    */
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    voxelGridScene->draw();
    //ofSetColor(255, 100, 100, 50);
    //ofVoxel.drawFaces();
    
    //box.drawNormals(10);

    /*Custom Voxel*/
    //mesh.draw();
    //mesh2.draw(); // fast!!
    //polyline.draw();
    //ofVoxel.draw();
    //boidSphere.draw();
    /*
    ofBackground(255,255,255,255); // draw a gradient in the background with ofBackgroundGradient(ofColor(10), ofColor(50));
    
    ofEnableDepthTest();
    cam.begin();
        
        roadMaterial.begin();
        plane.draw();
        
        for(size_t i = 0; i < BOIDS_COUNT; i++)
        {
            boidSpheres[i].draw();
        }
        
        spatialQueryCursor.draw(); // <------------------------------- 3D cursor draw call
    
        roadMaterial.end();
    
        plane.drawAxes(500);
        ofSetColor(100, 100, 100);
        box.drawWireframe();

    //
    //--------   Uniform grid
    //
        //emptyVoxelMAT.begin();
        
        for(size_t i = 0; i < uniformGrid.getGridSize(); i++)
        {
            ofVec3f pos = uniformGrid.getVoxelPositionByIndex(i);
            
            ofVoxelB.setGlobalPosition(pos.x + (VOXEL_SIZE/2), pos.y + (VOXEL_SIZE/2), pos.z - (VOXEL_SIZE/2));
            
            if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 0) // The voxel is an obstacle
            {
                ofSetColor(0, 0, 255, 80);
                ofVoxelB.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 1) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                ofVoxelB.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 0 && uniformGrid.getVoxelState(i) == 1)//Boid flys inside
            {
//                ofSetColor(0, 255, 0, 5);
//                ofVoxelB.drawFaces();
            }
            
            
            //This was supposed to visualize the vertices.
            //boidSphere.setGlobalPosition(pos.x, pos.y , pos.z);
        }
        //emptyVoxelMAT.end();
    
    ofDisableDepthTest();
    cam.end();
    
    //
    // GUI
    //
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
    */
}

//--------------------------------------------------------------
void ofApp::exit(){
    delete voxelGridScene;
}
/*
enum KeyCode // Printed 'key' inside keyPressed() to get the values
{
    W = 119,
    A = 97,
    S = 115,
    D = 100,
    SPACE = 32,
    UP = 57357,
    DOWN = 57359,
};*/

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    //voxelGridScene.pressedEvents();
    /*
    //std::cout << key << '\n';
    switch (key) {
        case KeyCode::W:
            //std::cout << "Front \n";
            spatialQueryPosition.z -= CURSOR_SPEED;
            break;
        case KeyCode::S:
            //std::cout << "Back \n";
            spatialQueryPosition.z += CURSOR_SPEED;
            break;
        case KeyCode::A:
            spatialQueryPosition.x -= CURSOR_SPEED;
            //std::cout << "Left \n";
            break;
        case KeyCode::D:
            spatialQueryPosition.x += CURSOR_SPEED;
            //std::cout << "Right \n";
            break;
        case KeyCode::SPACE:
            //std::cout << "Space \n";
            break;
        case KeyCode::UP:
            spatialQueryPosition.y += CURSOR_SPEED;
            //std::cout << "Up \n";
            break;
        case KeyCode::DOWN:
            spatialQueryPosition.y -= CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        default:
            break;
    }
    //std::cout << "cursor: "<<spatialQueryPosition << '\n';
    int cursorNewPos = uniformGrid.isPointInsideAVoxel(spatialQueryPosition);
    
    //std::cout << "Cursor Position in Grid: " << cursorNewPos<< '\n';
    //TEMPORAL using Boid's updatePositionInWorldGrid
    
    if(cursorNewPos == cursorCurrentPos)
    {
        cursorPreviousPos = cursorCurrentPos;
        return;
    }; //We have not moved to another voxel, do nothing
    
    //We have indeed change to another place
    cursorCurrentPos = cursorNewPos;
    
    if(cursorCurrentPos != -1) // We are still inside the grid, so notify the new voxel
        uniformGrid.addObjectToVoxel(cursorCurrentPos);
    
    
    if(cursorPreviousPos != -1) //The boid was not outside, notify previous voxel
        uniformGrid.removeObjectFromVoxel(cursorPreviousPos);
    
     //Update position.
    cursorPreviousPos = cursorCurrentPos;
    */
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
