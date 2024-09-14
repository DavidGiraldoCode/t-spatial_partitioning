#pragma once

#include "ofMain.h"
#include "Messenger.hpp"
#include "UniformGrid.hpp"
#include "ofxGui.h"
#include "Boid.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		
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
        const float CURSOR_SPEED = 50.0f;
};
