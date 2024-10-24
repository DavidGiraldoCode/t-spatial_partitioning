//
//  Scene.hpp
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

/**
 Recall: A vtable (virtual table) is a table of function pointers that is used to implement dynamic (runtime) polymorphism in C++. It allows objects of derived classes to invoke overridden functions based on their actual type, even when accessed via a pointer to a base class.
 **/

class Scene: public ofBaseApp
{
public:
    virtual ~Scene() {};
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
        Q = 113,
        E = 101,
        SPACE = 32,
        UP = 57357,
        DOWN = 57359,
        RIGHT = 57356,
        LEFT = 57358
    };
    //==================================== Meta data
    std::string sceneName = "";
    
    //==================================== Game settings
          int           BOIDS_COUNT = 100;
    const float         VOXEL_SIZE = 100;
    const unsigned      gridWidth = 20;
    const unsigned      gridHeight = 20;
    const unsigned      gridDepth = 30;
    const float         CURSOR_SPEED = 25.0f;
    
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
    UniformGrid                     uniformGrid;
    
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
