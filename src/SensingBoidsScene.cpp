//
//  SensingBoidsScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-14.
//
#include "SensingBoidsScene.hpp"

SensingBoidsScene::SensingBoidsScene(const std::string &name)
{
    sceneName = name;
    //sceneName = "Sensing Boids";
}

void SensingBoidsScene::setup()
{
    Scene::setup();
    drones = {};
    //drones.push_back(Drone());
    
    
    // ========== Boids
    BOIDS_COUNT = 1;
    boidsManager = BoidsManager(obstaclesBoundingVolume.getPosition(), BOIDS_COUNT, &uniformGrid);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++) //Instantiating the Boids in the center of the bounding volume
    {
        drones.push_back(Drone(ofVec3f(500,500,-500)));
    }

}

void SensingBoidsScene::update()
{
    
    boidsManager.updateSteeringForces();
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        drones[i].update(boidsManager.getBoids()[i].getPosition(),
                         boidsManager.getBoids()[i].getVelocity());
    }
}

void SensingBoidsScene::draw()
{
    ofBackground(255,255,255,255);
    
    ofEnableDepthTest();
    cam.begin();
    
        roadMaterial.begin();
        environmentGround.draw();
        roadMaterial.end();
        
        environmentGround.drawAxes(500);
        ofSetColor(100, 100, 100);
        obstaclesBoundingVolume.drawWireframe();
    // ==============================================  Rendering Drones
    for( auto &drone : drones)
    {
        drone.draw();
    }
    
    //===============================================  Rendering Uniform grid
        
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
    
    
    // =============================== GUI
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
}

void SensingBoidsScene::keyPressed(int key)
{
    
}
