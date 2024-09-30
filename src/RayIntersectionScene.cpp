//
//  RayIntersectionScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-30.
//
#include "RayIntersectionScene.hpp"

RayIntersectionScene::RayIntersectionScene()
{
    sceneName = "Ray Intersection";
};


RayIntersectionScene::~RayIntersectionScene()
{
    
};

void RayIntersectionScene::setup()
{
    Scene::setup();
    
    
    
    spatialQueryCursor.set(10,8);
    spatialQueryPosition = ofVec3f(0,0,0);
    spatialQueryCursor.setGlobalPosition(spatialQueryPosition.x, spatialQueryPosition.y, spatialQueryPosition.z);
    
};

void RayIntersectionScene::update()
{
    spatialQueryCursor.setGlobalPosition(spatialQueryPosition.x, spatialQueryPosition.y, spatialQueryPosition.z);
    rayMesh.setPosition(spatialQueryPosition);
    
    //The Ray starts at the spatialQuery sampler to a forward direction * the range of the ray.
    //upadate the ray vector
    manualTestRay.setOrigin(spatialQueryPosition);
    manualTestRay.setDirection(ofVec3f(0,0,-1)); // The forward vector in this scene is -1
    
    manualTestRay.getFirstIntersectionPoint(spatialQueryPosition, spatialQueryPosition + ofVec3f(0,0,1) * manualTestRay.getReach());
    rayMesh.lookAt(spatialQueryPosition + manualTestRay.getDirection() * manualTestRay.getReach());
    
    
    
    ofVec3f planeNormal = manualTestRay.getDirection() * -1;
    ofVec3f planePosition = ofVec3f(0, 0, VOXEL_SIZE * -1); // second plane in the Z axis away from the camera (depth)
    float lambaT;
    
    bool intersectionTest = manualTestRay.intersectPlane(planeNormal,
                                                         planePosition,
                                                         manualTestRay.getOrigin(),
                                                         manualTestRay.getDirection(),
                                                         lambaT);
    
//    std::cout << "intersectionTest: " << intersectionTest
//                << " | is intersection in Grid: " << uniformGrid.isPointInsideAVoxel(manualTestRay.getFristIntersection())
//                << "\n | is spatialQueryPosition in Grid: " << uniformGrid.isPointInsideAVoxel(spatialQueryPosition)
//                << "\n | spatialQueryPosition: " << spatialQueryPosition
//                << "\n | Ray FristIntersection: " << manualTestRay.getFristIntersection()
//                <<'\n';
    
    //TODO
    /**
     Visualize the voxels being intersertec by the ray
        Create the method for moving forward on the grid by units [i,j,k]
        Parametrize the Ray so it can be attached to the boid and compute the intersection.
     **/
};

void RayIntersectionScene::draw()
{
    ofBackground(255,255,255,255); // draw a gradient in the background with ofBackgroundGradient(ofColor(10), ofColor(50));
    
    ofEnableDepthTest();
    cam.begin();
        
        roadMaterial.begin();
        environmentGround.draw();
        roadMaterial.end();
        
        environmentGround.drawAxes(500);
        ofSetColor(100, 100, 100);
        obstaclesBoundingVolume.drawWireframe();
        
        spatialQueryCursor.draw(); // <------------------------------- 3D cursor draw call
        ofSetColor(100, 100, 255);
        rayMesh.drawWireframe(); //the dir vector of the bois an also the Ray

    //
    //--------   Uniform grid
    //
        //emptyVoxelMAT.begin();
        
        for(size_t i = 0; i < uniformGrid.getGridSize(); i++)
        {
            ofVec3f pos = uniformGrid.getVoxelPositionByIndex(i);
            
            voxelMesh.setGlobalPosition(pos.x + (VOXEL_SIZE/2), pos.y + (VOXEL_SIZE/2), pos.z - (VOXEL_SIZE/2));
            
            if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 0) // The voxel is an obstacle
            {
                ofSetColor(0, 0, 255, 80);
                voxelMesh.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 1) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                voxelMesh.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 0 && uniformGrid.getVoxelState(i) == 1)//Boid flys inside
            {
//                ofSetColor(0, 255, 0, 5);
//                voxelMesh.drawFaces();
            }
        }
        //emptyVoxelMAT.end();
    
    ofDisableDepthTest();
    cam.end();
    
    //
    // GUI
    //
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
};

void RayIntersectionScene::keyPressed(int key)
{
    
    std::cout << key << '\n';
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
    
    //Updating position of cursor in Voxel Grid
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
}
