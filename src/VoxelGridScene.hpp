//
//  VoxelGridScene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-24.
//
#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "ofBaseApp.h"
#include "UniformGrid.hpp"
#include "ofxGui.h"
#include "Boid.hpp"

class VoxelGridScene : public ofBaseApp
{
public:
    VoxelGridScene();
    ~VoxelGridScene();
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    
    enum KeyCode // Printed 'key' inside keyPressed() to get the values
    {
        W = 119,
        A = 97,
        S = 115,
        D = 100,
        SPACE = 32,
        UP = 57357,
        DOWN = 57359,
    };
    
    //==================================== Game settings
    const int           BOIDS_COUNT = 100;
    const float         VOXEL_SIZE = 200;
    const unsigned      gridWidth = 10;
    const unsigned      gridHeight = 10;
    const unsigned      gridDepth = 15;
    const float         CURSOR_SPEED = 50.0f;
    
    //==================================== Game state
    bool                isInside = false;
    int                 cursorCurrentPos = -1;
    int                 cursorPreviousPos = -1;
    
    //==================================== Camera
    ofEasyCam           cam;
    
    //==================================== Ligths
    ofLight             light;// = ofLight();
    
    //==================================== Materials
    ofMaterial          roadMaterial;
    ofMaterial          emptyVoxelMAT;
    
    //==================================== Actors
    ofBoxPrimitive                  obstaclesBoundingVolume;
    ofPlanePrimitive                environmentGround;
    ofBoxPrimitive                  voxelMesh;
    std::vector<Boid>               boids = {};
    std::vector<ofSpherePrimitive>  boidMeshes = {};
    ofSpherePrimitive               boidSphere;
    UniformGrid                     uniformGrid;
    
    //Sphere representing a 3D point moved by WASD and UP DOWN to query the space
    ofSpherePrimitive               spatialQueryCursor;
    ofVec3f                         spatialQueryPosition;
    
    //==================================== GUI
    ofParameter<float>      guiFramesPerSecond;
    ofParameter<int>        guiVoxelResolution;

    ofParameter<unsigned>   guiGridWidth;
    ofParameter<unsigned>   guiGridHeight;
    ofParameter<unsigned>   guiGridDepth;

    ofParameter<ofColor>    color;
    ofParameter<glm::vec2>  center;
    ofParameter<int>        circleResolution;
    ofParameter<bool>       guiVoxelVisibility;
    ofxButton               twoCircles;
    ofxButton               ringButton;
    ofParameter<string>     screenSize;

    ofxPanel                gui;
    
};
