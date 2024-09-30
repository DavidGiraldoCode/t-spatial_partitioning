//
//  Scene.cpp
//  s-spatial_partitioning
//  Stores all the objects
//
//  Created by David MacBook on 2024-09-11.
//

#include "Scene.hpp"

void Scene::setup()
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

    gui.setup(sceneName); // most of the time you don't need a name but don't forget to call setup
    gui.add(guiFramesPerSecond.set( "FPS", 1));
    //gui.add(guiVoxelResolution.set( "Voxels", 1, 1, 100));
    
    //gui.add(guiVoxelVisibility.set("Voxel visibility", true));
    //gui.add(center.set("center",glm::vec2(ofGetWidth()*.5,ofGetHeight()*.5),glm::vec2(0,0),glm::vec2(ofGetWidth(),ofGetHeight())));
    //gui.add(color.set("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    //gui.add(circleResolution.set("circleRes", 5, 3, 90));
    //gui.add(twoCircles.setup("twoCircles"));
    //gui.add(ringButton.setup("ring"));
    //gui.add(screenSize.set("screenSize", ""));
    //gui.add(guiGridWidth.set( "Grid Width", 1, 1, 100));
    //gui.add(guiGridHeight.set( "Grid Height", 1, 1, 100));
    //gui.add(guiGridDepth.set( "Grid Depth", 1, 1, 100));

    //
    //--------   Uniform grid
    //
    //voxelGridResolution = 1;
    
    
    //ofobstaclesBoundingVolume mesh that represets the bounding volume of the environmental obstacles
    obstaclesBoundingVolume.set( gridWidth * VOXEL_SIZE, gridHeight * VOXEL_SIZE, gridDepth * VOXEL_SIZE);
    obstaclesBoundingVolume.setGlobalPosition(obstaclesBoundingVolume.getWidth()/2, obstaclesBoundingVolume.getHeight()/2, obstaclesBoundingVolume.getDepth()/2 * -1);
    obstaclesBoundingVolume.setResolution(1);
    
    //ofQuad that represents the floor of the scene
    environmentGround.set(gridWidth * VOXEL_SIZE, gridDepth * VOXEL_SIZE ,gridWidth, gridDepth);
    environmentGround.rotateDeg(-90, glm::vec3{1,0,0});
    //environmentGround.move(0, -49, 0);
    environmentGround.setGlobalPosition(environmentGround.getWidth()/2, 0, obstaclesBoundingVolume.getDepth()/2 * -1);
        
    //
    // Voxel GRID
    //
    
    uniformGrid = UniformGrid(gridWidth, gridHeight, gridDepth, VOXEL_SIZE);
    std::cout << "Grid size:" << uniformGrid.getGridSize() << '\n';
    
    //ofPrimivite Sphere Mesh to represent the Boid
    voxelMesh.set(VOXEL_SIZE);
    voxelMesh.setGlobalPosition(voxelMesh.getHeight()/2 + voxelMesh.getHeight(), voxelMesh.getHeight()/2, -voxelMesh.getHeight()/2);
    voxelMesh.setResolution(1);
    
    ofFloatColor emptyColor(1,1,1,0.1);
    emptyVoxelMAT.setDiffuseColor(emptyColor);
    
    //
    // LIGHT SETTINGS
    //
    
    light.setup();
    light.setPosition(obstaclesBoundingVolume.getWidth()/2, obstaclesBoundingVolume.getHeight(), obstaclesBoundingVolume.getDepth()/2 * -1);
    light.setAmbientColor(ofFloatColor(0.4, 1.0));
}

void Scene::update()
{

    
}

void Scene::draw()
{
//    ofBackground(255,255,255,255); // draw a gradient in the background with ofBackgroundGradient(ofColor(10), ofColor(50));
//    
//    ofEnableDepthTest();
//    cam.begin();
//        
//        roadMaterial.begin();
//        environmentGround.draw();
//        
//        roadMaterial.end();
//    
//        environmentGround.drawAxes(500);
//        ofSetColor(100, 100, 100);
//        obstaclesBoundingVolume.drawWireframe();
//  
//    
//    ofDisableDepthTest();
//    cam.end();
//    
//    //
//    // GUI
//    //
//    guiFramesPerSecond.set(ofGetFrameRate());
//    gui.draw();
}

void Scene::keyPressed(int key)
{
    
}
