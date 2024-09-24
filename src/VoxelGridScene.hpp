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
    
    //new stuff
    ofLight light;// = ofLight();
    ofEasyCam cam;

    ofBoxPrimitive box;
    ofPlanePrimitive plane;
    
    ofMaterial roadMaterial;

    /* Custom Voxel*/
    ofVboMesh mesh;
    ofVboMesh mesh2;
    ofPolyline polyline;

    ofBoxPrimitive ofVoxel;
    ofBoxPrimitive ofVoxelB;

    /*Boid behaviour*/
    std::vector<Boid> boids = {};
    std::vector<ofSpherePrimitive> boidSpheres = {};
    //Boid boid;
    ofSpherePrimitive boidSphere;
    
    /*GUI*/

    ofParameter<float> guiFramesPerSecond;
    ofParameter<int> guiVoxelResolution;

    ofParameter<unsigned> guiGridWidth;
    ofParameter<unsigned> guiGridHeight;
    ofParameter<unsigned> guiGridDepth;

    ofParameter<ofColor> color;
    ofParameter<glm::vec2> center;
    ofParameter<int> circleResolution;
    ofParameter<bool> guiVoxelVisibility;
    ofxButton twoCircles;
    ofxButton ringButton;
    ofParameter<string> screenSize;

    ofxPanel gui;

    // Uniform spatial partitioning
    //configurations for the test
    int voxelGridResolution;
    unsigned gridWidth, gridHeight, gridDepth;
    //UniformGrid uniformGrid; //= UniformGrid(2,2,2, ofVec3f(0,0,0),ofVec3f(10,10,10));
    UniformGrid uniformGrid;// = UniformGrid(gridWidth, gridHeight, gridDepth, ofVec3f(0,0,0));
    ofMaterial emptyVoxelMAT;

    //Sphere representing a 3D point moved by WASD and UP DOWN to query the space
    ofSpherePrimitive spatialQueryCursor;
    ofVec3f spatialQueryPosition;
    int cursorCurrentPos = -1;
    int cursorPreviousPos = -1;
    const float CURSOR_SPEED = 50.0f;
};
