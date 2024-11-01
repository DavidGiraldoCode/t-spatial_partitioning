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
    rays = {};
    //drones.push_back(Drone());
    
    
    // ========== Boids
    BOIDS_COUNT = 20;
    ofVec3f spawnPoint  = ofVec3f(980,950, 8000);
    //boidsManager = BoidsManager(obstaclesBoundingVolume.getPosition(), BOIDS_COUNT, &uniformGrid);
    boidsManager = BoidsManager(spawnPoint, BOIDS_COUNT, &uniformGrid);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++) //Instantiating the Boids in the center of the bounding volume
    {
        drones.push_back(Drone(spawnPoint));
        
        rays.push_back(Ray());
        ofVec3f direction = ofVec3f(boidsManager.getBoids()[i].getVelocity());
        rays[i].setDirection(direction.normalize());
    }

}
void computeAxisAlignPlaneIntersection( Boid& currentBoid,
                                  const ofVec3f & worldNormal,
                                        UniformGrid & uniformGridRef,
                                        Ray & testRay,
                                        ofVec3f & planeNormal,
                                  const float startingIndex,
                                  const float range,
                                        float lamba,
                                  const float stepSize)
{
    
    // If ray is going in the same direction as the world normal, the PlaneNormal needs to flip
    // to consider the voxels' faces that are in the direction [MaxBound -> 0]
    if(worldNormal.dot(testRay.getDirection()) > 0)
        planeNormal *= -1;
        
    // dot = 0 means that the ray is orthogonal to the world, and thus no intersection happens (or infinite)
    if(worldNormal.dot(testRay.getDirection()) != 0)
    {
        int planeIndex; // If the plane normal is negative, we traverse the planes from [depth -> 0]
//        std::cout << planeNormal       << " PlaneNormal\n";
//        std::cout << testRay.getDirection() << " Ray Direction\n";
//        std::cout << testRay.getOrigin()    << " Ray Origin\n";
//        std::cout << startingIndex      << " startingIndex\n";
//        std::cout << range              << " range\n";
        
        ofVec3f planePosition;
        
        for(size_t i = 1; i <= (range - startingIndex); i++)
        {
            /**
            depthRange - index3D.z = absoluteDistance
            since depthRange - absoluteDistance = index3D.z, we use this equation to offset the plane position adding (or substrating) i
            depthRange - absoluteDistance - i = index3D.z - i
             **/
            // -1 becase the voxel grid grows away from the camera.
            
            //std::cout << planeIndex << " planeIndex\n";
            int flip; // -1 becase the grid grows away from the camera, but only for Z
            if(planeNormal.z != 0)
                flip = i == 0 ? 1 : -1; // Sneaky way to avoid having -0
            else
                flip = 1;
            
            if(planeNormal.x != 0) // Meaning, is the X axis what is being tested
            {
                planeIndex = planeNormal.x == 1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.x = planeIndex * stepSize;
            }
            if(planeNormal.y != 0) // Meaning, is the Y axis what is being tested
            {
                planeIndex = planeNormal.y == 1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.y = planeIndex * stepSize;
            }
                
            if(planeNormal.z != 0) // Meaning, is the Z axis what is being tested
            {
                planeIndex = planeNormal.z == -1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.z = planeIndex * stepSize * flip;
            }
                
            
            
            bool intersectionTest = testRay.intersectPlane(planeNormal,
                                                           planePosition,
                                                           testRay.getOrigin(),
                                                           testRay.getDirection(),
                                                           lamba);
            //stop doing intersection test because
            // 1. Lamba may be grater than the reach
//            std::cout << planePosition << " PlanePosition | "
//                      << intersectionTest << " intersectionTest | "
//                      << testRay.getIntersectionPoint() << " Intersection Point |\n";
            
            if (!intersectionTest) break; //This avoiding jumping voxels
            
            int voxelIndex = uniformGridRef.isPointInsideAVoxelGivenRayDirection(testRay.getIntersectionPoint(),
                                                                                 planeNormal,
                                                                                 testRay.getDirection());
            
            //std::cout << uniformGridRef.get3DunitIndex(testRay.getIntersectionPoint()) << " 3D index \n";
            uniformGridRef.setIntersection(voxelIndex);
            
            if(uniformGridRef.isVoxelAnObstacle(voxelIndex))
            {
                //Start avoidanceProtocol on the Boid
                // We need the World location of the voxel
                //std::cout << testRay.getIntersectionPoint() << " intersection point\n";
                ofVec3f obstacle = uniformGridRef.getVoxelWorldCenterPosition(voxelIndex); //testRay.getIntersectionPoint();
                //std::cout << obstacle << " obstacle center\n";
                currentBoid.activateAvoidanceProtocol(obstacle);
                break; //Stops sensing
            }
            else if(i == (range - startingIndex)) // if the traversal reaches the edge and did not find any obstacles
            {
                currentBoid.deactivateAvoidanceProtocol();
            }
                
        }
        //std::cout << '\n';
    }
}

void SensingBoidsScene::update()
{
    
    boidsManager.updateSteeringForces();
    ofVec3f xPlaneNormal = ofVec3f(1,0,0);
    ofVec3f yPlaneNormal = ofVec3f(0,1,0);
    ofVec3f zPlaneNormal = ofVec3f(0,0,1);//ray.getDirection() * -1;
    
    ofVec3f world_X_Normal = ofVec3f(1,0,0);
    ofVec3f world_Y_Normal = ofVec3f(0,1,0);
    ofVec3f world_Z_Normal = ofVec3f(0,0,1);
    
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        Boid& boid = boidsManager.getBoids()[i];
        ofVec3f boidPos = boid.getPosition();
        ofVec3f boidDir = ofVec3f(boid.getVelocity()).normalize();
        
        drones[i].update(boid.getPosition(),
                         boid.getVelocity());
        
        //upadate the ray vector
        rays[i].setOrigin(boidPos);
        rays[i].setDirection(boidDir); // The forward vector in this scene is -1
        
        float lambaT;
        
        // Ray testing STARTING POINT
        // This is the position inside the 3D array from where the ray traversal test will start with respect to the Voxel Grid
        // 0 based [0,0,0] -> [width - 1, height - 1, depth - 1] inclusive, meaning uniformGrid[width, height, depth] is NOT a valid position within bounds
        ofVec3f index3D = uniformGrid.get3DunitIndex(rays[i].getOrigin());
        
        float depthRange = index3D.z + (int)(rays[i].getReach()/VOXEL_SIZE); //how far along the depth it should go
        float widthRange = index3D.x + (int)(rays[i].getReach()/VOXEL_SIZE); //how far along the width planes it should go
        float heightRange = index3D.y + (int)(rays[i].getReach()/VOXEL_SIZE); //how far along the height planes it should go
        
        computeAxisAlignPlaneIntersection(boid, world_X_Normal, uniformGrid, rays[i], xPlaneNormal, index3D.x, widthRange, lambaT, VOXEL_SIZE);
        computeAxisAlignPlaneIntersection(boid, world_Y_Normal, uniformGrid, rays[i], yPlaneNormal, index3D.y, heightRange, lambaT, VOXEL_SIZE);
        computeAxisAlignPlaneIntersection(boid, world_Z_Normal, uniformGrid, rays[i], zPlaneNormal, index3D.z, depthRange, lambaT, VOXEL_SIZE);
        
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
//            else if(uniformGrid.getVoxelObstacle(i) == 0 && uniformGrid.getVoxelState(i) == 1)//Boid flys inside
//            {
////                ofSetColor(0, 255, 0, 5);
////                voxelMesh.drawFaces();
//            }
            //voxelMesh.drawWireframe();
            
            // VISUALIZING INTERSECTIONS
            
            if(uniformGrid.getVoxelIntersectionState(i) == true) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                //voxelMesh.drawFaces();
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
