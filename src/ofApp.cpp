#include "ofApp.h"


/*
 In OpenGL Y is Up
 */
const int BOIDS_COUNT = 1;
//--------------------------------------------------------------
void ofApp::setup(){
    std::cout << "Hello in setup" << '\n';
    
    Messenger myMessenger = Messenger();
    
    /* Custom Voxel*/
    mesh.addVertex(ofVec3f(0,0,0));
    mesh.addColor(ofColor::red);
    mesh.addVertex(ofVec3f(100,0,0));
    mesh.addColor(ofColor::red);
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh2 = mesh;
    
    ofVec3f pointA = ofVec3f(0,0,0);
    ofVec3f pointB = ofVec3f(100,0,0);
    ofVec3f pointC = ofVec3f(0,100,0);
    ofVec3f pointD = ofVec3f(100,100,0);
    
    ofVec3f pointE = ofVec3f(0,0,100);
    ofVec3f pointF = ofVec3f(100,0,100);
    ofVec3f pointG = ofVec3f(0,100,100);
    ofVec3f pointI = ofVec3f(100,100,100);
    
    polyline.lineTo(pointA.x,pointA.y,pointA.z);
    polyline.lineTo(pointB.x,pointB.y,pointB.z);
    polyline.lineTo(pointD.x,pointD.y,pointD.z);
    polyline.lineTo(pointC.x,pointC.y,pointC.z);
    polyline.lineTo(pointA.x,pointA.y,pointA.z);
    
    polyline.lineTo(pointE.x,pointE.y,pointE.z);
    polyline.lineTo(pointF.x,pointF.y,pointF.z);
    polyline.lineTo(pointI.x,pointI.y,pointI.z);
    polyline.lineTo(pointG.x,pointG.y,pointG.z);
    polyline.lineTo(pointE.x,pointE.y,pointE.z);
    
    polyline.close();
    //ofVoxel
    ofVoxel.set(100);
    ofVoxel.setGlobalPosition(ofVoxel.getHeight()/2, ofVoxel.getHeight()/2, -ofVoxel.getHeight()/2);
    ofVoxel.setResolution(1);
    
    

    
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
    

    ofFloatColor roadColor(1,0,0,0.2);
    roadMaterial.setDiffuseColor(roadColor);
    
    
    //roadColor.a = 1.0;
    //roadMaterial.setDiffuseColor(roadColor);
    //roadMaterial.setShininess(0.01);

    //Set our camera up in a nice location to view our awesome car
    //-965, 586, -1084
    //cam.setPosition(-965,2000,-1000);
    
    cam.setGlobalPosition(0, 500, 1500);
    //cam.lookAt(truck.getNode(), {0.f, 1.f, 0.f});
    //cam.setNearClip(0);
    cam.setFarClip(10000);
    
    /*Boid*/
    //boid = Boid(ofVec3f(box.getPosition()).x, ofVec3f(box.getPosition()).y, ofVec3f(box.getPosition()).z);
   // boidSphere.setGlobalPosition(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids.push_back(Boid(ofVec3f(box.getPosition()).x, ofVec3f(box.getPosition()).y, ofVec3f(box.getPosition()).z));
        boidSpheres.push_back(ofSpherePrimitive());
        boidSpheres[i].set(10, 16);
    }
    
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
    gui.add(guiGridWidth.set( "Grid Width", 1, 1, 100));
    gui.add(guiGridHeight.set( "Grid Height", 1, 1, 100));
    gui.add(guiGridDepth.set( "Grid Depth", 1, 1, 100));

    // 
    //--------   Uniform grid
    //
    voxelGridResolution = 1;
    gridWidth = 2;
    gridHeight = 2;
    gridDepth = 2;
    float VOXEL_SIZE = 500;
    uniformGrid = UniformGrid(gridWidth, gridHeight, gridDepth, ofVec3f(0,0,0), VOXEL_SIZE);
    boidSphere.set(10, 16);
    std::cout << "Grid size:" << uniformGrid.getGridSize() << '\n';
    
    ofVoxelB.set(VOXEL_SIZE);
    ofVoxelB.setGlobalPosition(ofVoxelB.getHeight()/2 + ofVoxel.getHeight(), ofVoxelB.getHeight()/2, -ofVoxelB.getHeight()/2);
    ofVoxelB.setResolution(1);
    
    ofFloatColor emptyColor(1,1,1,0.1);
    emptyVoxelMAT.setDiffuseColor(emptyColor);
}

//--------------------------------------------------------------
void ofApp::update(){
    /*Custom Voxel*/
    //mesh.getVertices()[1].x+=0.1;
    //mesh2.getVertices()[1].x=mesh.getVertices()[1].x + 0.1;
    //boid.move();
    //boid.applyBoundingForce(ofVec3f(box.getPosition()), box.getWidth(), box.getHeight(), box.getDepth());
    //boidSphere.setGlobalPosition(boid.getPosition().x, boid.getPosition().y, boid.getPosition().z);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids[i].applyBoundingForce(ofVec3f(box.getPosition()), box.getWidth(), box.getHeight(), box.getDepth());
        boids[i].move();
        boidSpheres[i].setGlobalPosition(boids[i].getPosition().x, boids[i].getPosition().y, boids[i].getPosition().z);
        
        uniformGrid.isPointInsideAVoxel(boids[i].getPosition());
    }
    
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
        //ofVoxel.draw();
        
        //boidSphere.draw();
        for(size_t i = 0; i < BOIDS_COUNT; i++)
        {
            boidSpheres[i].draw();
        }
        roadMaterial.end();
    
        plane.drawAxes(500);
        ofSetColor(50, 50, 50);
        box.drawWireframe();
    
        
        ofSetColor(255, 100, 100, 50);
        //ofVoxel.drawFaces();
        
        //box.drawNormals(10);
    
        /*Custom Voxel*/
        //mesh.draw();
        //mesh2.draw(); // fast!!
        //polyline.draw();
    //
    //--------   Uniform grid
    //
        //emptyVoxelMAT.begin();
        ofSetColor(255, 255, 255, 10);
        for(size_t i = 0; i < uniformGrid.getGridSize(); i++)
        {
            ofVec3f pos = uniformGrid.getVoxelPositionByIndex(i);
            
            ofVoxelB.setGlobalPosition(pos.x, pos.y, pos.z);
            ofVoxelB.drawFaces();
            
            boidSphere.setGlobalPosition(pos.x, pos.y, pos.z);
            boidSphere.draw();
        }
        //emptyVoxelMAT.end();
    
    ofDisableDepthTest();
    cam.end();
    
    /*GUI*/
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
    
    //
    //--------   Uniform grid
    //
    
    
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
