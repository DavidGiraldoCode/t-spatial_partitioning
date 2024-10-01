//
//  BoidsNaiveScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
#include "BoidsNaiveScene.hpp"

BoidsNaiveScene::BoidsNaiveScene()
{
    sceneName = "Boids Naive";
};

BoidsNaiveScene::~BoidsNaiveScene()
{
    
}

void BoidsNaiveScene::setup()
{
    Scene::setup();

    //==================================== Actors
    BOIDS_COUNT = 500;
    boidsManager = BoidsManager(obstaclesBoundingVolume.getPosition(), BOIDS_COUNT, &uniformGrid);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++) //Instantiating the Boids in the center of the bounding volume
    {
        boidMeshes.push_back(ofSpherePrimitive());
        boidMeshes[i].set(10, 16); //radius and resolution
    }
    
    //==================================== GUI
    
    gui.add(guiSeparationF.set( "Separation F", boidsManager.SEPARATION_FACTOR, 0, 10));
    gui.add(guiCohesionF.set( "Cohesion F", boidsManager.COHESION_FACTOR, 0, 10));
    gui.add(guiAlignmentF.set( "Alignment F", boidsManager.ALIGNMENT_FACTOR, 0, 10));
    
    gui.add(guiSeparationDistance.set( "Separation Dist", boidsManager.neighborSeparationDistance, 0, 500));
    gui.add(guiCohesionDistance.set( "Cohesion Dist", boidsManager.neighborCohesionDistance, 0, 500));
    gui.add(guiAlignmentDistance.set( "Alignment Dist", boidsManager.neighborAlignmentDistance, 0, 500));
   
}
void BoidsNaiveScene::update()
{
    boidsManager.updateSteeringForces();
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
//        boids[i].applyBoundingForce(ofVec3f(obstaclesBoundingVolume.getPosition()),
//                                    obstaclesBoundingVolume.getWidth(),
//                                    obstaclesBoundingVolume.getHeight(),
//                                    obstaclesBoundingVolume.getDepth());
        //boids[i].updateSteeringForces();
        ofVec3f pos = boidsManager.getBoids()[i].getPosition();
        boidMeshes[i].setGlobalPosition(pos.x, pos.y, pos.z);
        
        //boids[i].updatePositionInWorldGrid(uniformGrid);
    }
    
}
void BoidsNaiveScene::draw()
{
    ofBackground(255,255,255,255);
    ofEnableDepthTest();
    cam.begin();
        
        roadMaterial.begin();
        environmentGround.draw();
        roadMaterial.end();
    
        for(size_t i = 0; i < BOIDS_COUNT; i++)
        {
            boidMeshes[i].draw();
        }
        
        environmentGround.drawAxes(500);
        ofSetColor(100, 100, 100);
        obstaclesBoundingVolume.drawWireframe();
        
        ofSetColor(100, 100, 255);
    
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
        }
        //emptyVoxelMAT.end();
    
    ofDisableDepthTest();
    cam.end();
    
    //==================================== GUI
    
    boidsManager.SEPARATION_FACTOR = guiSeparationF;
    boidsManager.COHESION_FACTOR = guiCohesionF;
    boidsManager.ALIGNMENT_FACTOR = guiAlignmentF;
    
    boidsManager.neighborCohesionDistance = guiCohesionDistance;
    boidsManager.neighborSeparationDistance = guiSeparationDistance;
    boidsManager.neighborAlignmentDistance = guiAlignmentDistance;
    
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
}
void BoidsNaiveScene::keyPressed(int key)
{
    
}
