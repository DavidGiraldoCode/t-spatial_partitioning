//
//  RayIntersectionScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-30.
//
/**
 TODO:
 Use the position of the RayOrigin in the Grid to define from where the steps of the intersection test will start. Avoinding O(w * h * d)
 Use the Ray reach to define how many steps to compute, intead of doing it by checking the "lamba t"
 Use the inidividual X Y Z components of the Ray direction to determine if the test will move forward or backward in the grid.
 Evaluate if it usueful to get the (i, j, k) 3D indices from the Grid.
 **/
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
    
    
    ray = Ray();
    rayOriginPosition = ofVec3f(0,0,0);
    rayTargetPosition = ofVec3f(gridWidth * VOXEL_SIZE / 2,
                                gridHeight * VOXEL_SIZE / 2,
                                gridDepth * VOXEL_SIZE / -2);
    ray.setDirection((rayTargetPosition-rayOriginPosition).normalize());//ofVec3f(0,0,-1)); // Forward Z (-1)
    
    //Create the meshes to visualize the ray origin, target and reach
    rayOriginMesh.set(20,8);
    rayTargetMesh.set(10,8);
    
    //The ray mesh needs to be define in local space.
    rayMesh.getMesh().addVertex(ofVec3f(-5,0,0));
    rayMesh.getMesh().addVertex(ofVec3f(0,0,ray.getReach() * -1));//ray.getDirection() * ray.getReach());
    rayMesh.getMesh().addVertex(ofVec3f(5,0,0));
    rayMesh.getMesh().setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    rayOriginMesh.setGlobalPosition(rayOriginPosition.x, rayOriginPosition.y, rayOriginPosition.z);
    rayTargetMesh.setGlobalPosition(rayTargetPosition.x, rayTargetPosition.y, rayTargetPosition.z);
    
};


void RayIntersectionScene::update()
{
    //upadate the ray vector
    ray.setOrigin(rayOriginPosition);
    ray.setDirection((rayTargetPosition - rayOriginPosition).normalize()); // The forward vector in this scene is -1
    
    ofVec3f xPlaneNormal = ofVec3f(1,0,0);
    ofVec3f yPlaneNormal = ofVec3f(0,1,0);
    ofVec3f zPlaneNormal = ofVec3f(0,0,1);//ray.getDirection() * -1;
    
    float lambaT;
    //X planes
    for(size_t i = 0; i <= gridWidth; i++)
    {
        ofVec3f planePosition = ofVec3f(i * VOXEL_SIZE, 0, 0); // second plane in the Z axis away from the camera (depth)
        bool intersectionTest = ray.intersectPlane(  xPlaneNormal,
                                                     planePosition,
                                                     ray.getOrigin(),
                                                     ray.getDirection(),
                                                     lambaT);
        
        int voxelIndex = uniformGrid.isPointInsideAVoxel(ray.getIntersectionPoint());
        uniformGrid.setIntersection(voxelIndex);
    }
    //Y planes
    for(size_t i = 0; i <= gridHeight; i++)
    {
        ofVec3f planePosition = ofVec3f(0, i * VOXEL_SIZE, 0); // second plane in the Z axis away from the camera (depth)
        bool intersectionTest = ray.intersectPlane(  yPlaneNormal,
                                                     planePosition,
                                                     ray.getOrigin(),
                                                     ray.getDirection(),
                                                     lambaT);
        
        int voxelIndex = uniformGrid.isPointInsideAVoxel(ray.getIntersectionPoint());
        uniformGrid.setIntersection(voxelIndex);
    }
    
    //Z planes
    for(size_t i = 0; i <= gridDepth; i++)
    {
        ofVec3f planePosition = ofVec3f(0, 0, i * VOXEL_SIZE * -1); // second plane in the Z axis away from the camera (depth)
        bool intersectionTest = ray.intersectPlane(  zPlaneNormal,
                                                     planePosition,
                                                     ray.getOrigin(),
                                                     ray.getDirection(),
                                                     lambaT);
        
        int voxelIndex = uniformGrid.isPointInsideAVoxel(ray.getIntersectionPoint());
        uniformGrid.setIntersection(voxelIndex);
    }
    
    /*
     std::cout << "intersectionTest: " << intersectionTest
             << "\n | Ray Origin Position: " << rayOriginPosition
             << "\n | Ray ["<< i <<"] Intersection Point: " << ray.getIntersectionPoint()
             << "\n | Intersection ["<< i <<"] Point Index in Grid: " << voxelIndex
             << "\n | Ray Origin Position in Grid: " << uniformGrid.isPointInsideAVoxel(rayOriginPosition)
             <<'\n';
     */
    
    //Update visulizer
    rayOriginMesh.setGlobalPosition(rayOriginPosition.x, rayOriginPosition.y, rayOriginPosition.z);
    rayTargetMesh.setGlobalPosition(rayTargetPosition.x, rayTargetPosition.y, rayTargetPosition.z);
    rayMesh.setPosition(rayOriginPosition);
    
    rayMesh.lookAt(rayTargetPosition);
    
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
        
        rayOriginMesh.draw(); // <------------------------------- 3D cursor draw call
        
        ofSetColor(255, 100, 100);
        rayTargetMesh.draw();
        rayMesh.drawWireframe(); //the dir vector of the bois an also the Ray

    //
    //--------   Uniform grid
    //
        
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
            //voxelMesh.drawWireframe();
            
            // VISUALIZING INTERSECTIONS
            
            if(uniformGrid.getVoxelIntersectionState(i) == true) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                voxelMesh.drawFaces();
            }
        }
    uniformGrid.clearIntersections();
    
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

    switch (key) {
        case KeyCode::W:
            //std::cout << "Front \n";
            rayOriginPosition.z -= CURSOR_SPEED;
            break;
        case KeyCode::S:
            //std::cout << "Back \n";
            rayOriginPosition.z += CURSOR_SPEED;
            break;
        case KeyCode::A:
            rayOriginPosition.x -= CURSOR_SPEED;
            //std::cout << "Left \n";
            break;
        case KeyCode::D:
            rayOriginPosition.x += CURSOR_SPEED;
            //std::cout << "Right \n";
            break;
        case KeyCode::Q: // DOWN
            rayOriginPosition.y -= CURSOR_SPEED;
            break;
        case KeyCode::E: // UP
            rayOriginPosition.y += CURSOR_SPEED;
            break;
        case KeyCode::SPACE:
            //std::cout << "Space \n";
            break;
        case KeyCode::UP:
            rayTargetPosition.y += CURSOR_SPEED;
            //std::cout << "Up \n";
            break;
        case KeyCode::DOWN:
            rayTargetPosition.y -= CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        case KeyCode::RIGHT:
            rayTargetPosition.x -= CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        case KeyCode::LEFT:
            rayTargetPosition.x += CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        default:
            break;
    }
    
    //Updating position of cursor in Voxel Grid
    //std::cout << "cursor: "<<rayOriginPosition << '\n';
    int cursorNewPos = uniformGrid.isPointInsideAVoxel(rayOriginPosition);
    
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
