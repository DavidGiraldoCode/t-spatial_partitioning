//
//  VoxelGridScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-24.
//

#include "VoxelGridScene.hpp"

VoxelGridScene::VoxelGridScene()
{
    std::cout << "This is a custom scene that inherits form ofBase \n";
}

VoxelGridScene::~VoxelGridScene()
{
    std::cout << "Bye VoxelGridScene \n";
}

const int BOIDS_COUNT = 100;
float VOXEL_SIZE = 200;

void VoxelGridScene::setup()
{
    std::cout << "VoxelGridScene setup \n";
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
    uniformGrid = UniformGrid(gridWidth, gridHeight, gridDepth, /*ofVec3f(0,0,0),*/ VOXEL_SIZE);
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
}
bool isInside = false;
void VoxelGridScene::update()
{
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids[i].applyBoundingForce(ofVec3f(box.getPosition()), box.getWidth(), box.getHeight(), box.getDepth());
        boids[i].move();
        boidSpheres[i].setGlobalPosition(boids[i].getPosition().x, boids[i].getPosition().y, boids[i].getPosition().z);
        
        boids[i].updatePositionInWorldGrid(uniformGrid);
        //isInside = uniformGrid.isPointInsideAVoxel(boids[i].getPosition());
    }
    
    
    
    spatialQueryCursor.setGlobalPosition(spatialQueryPosition.x, spatialQueryPosition.y, spatialQueryPosition.z);
    
    
}

void VoxelGridScene::draw()
{
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
}
