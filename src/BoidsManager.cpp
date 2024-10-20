//
//  BoidsManager.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
#include "BoidsManager.hpp"

BoidsManager::BoidsManager(const ofVec3f &spawnPoint, int BOIDS_COUNT, UniformGrid *uniformGrid)
{
    boids = {};
    uniformGridRef = uniformGrid;
    //Instantiating the Boids in the center of the bounding volume
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids.push_back(Boid(spawnPoint));
        boids[i].SEPARATION_FACTOR = SEPARATION_FACTOR;
        boids[i].COHESION_FACTOR = COHESION_FACTOR;
        boids[i].ALIGNMENT_FACTOR = ALIGNMENT_FACTOR;
        boids[i].AVOIDANCE_FACTOR = AVOIDANCE_FACTOR;
    }
    std::cout<<neighborCohesionDistance << ' '
    <<neighborSeparationDistance << ' '
    <<neighborAlignmentDistance
    <<'\n';
}
                        
void BoidsManager::updateSteeringForces()
{
    
    for(size_t i = 0; i < boids.size(); i++)
    {
        boids[i].SEPARATION_FACTOR = SEPARATION_FACTOR;
        boids[i].COHESION_FACTOR = COHESION_FACTOR;
        boids[i].ALIGNMENT_FACTOR = ALIGNMENT_FACTOR;
        
        for(size_t j = 0; j < boids.size(); j++)
        {
            if(i != j)
            {
                
                ofVec3f distVec = boids[j].getPosition() - boids[i].getPosition();
                float sqrDistance = distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z;
                
                //COHESION
                if(sqrDistance < (neighborCohesionDistance*neighborCohesionDistance))
                {
                    boids[i].numPerceivedNCohesion++;
                    boids[i].flockCentroid += boids[j].getPosition();
                }
                //ALIGNMENT
                if(sqrDistance < (neighborAlignmentDistance*neighborAlignmentDistance))
                {
                    boids[i].numPerceivedNAlignment++;
                    boids[i].flockAverageAlignment += boids[j].velocity;
                }
                //SEPARETION
                if(sqrDistance < (neighborSeparationDistance*neighborSeparationDistance))
                {
                    //boids[i].numPerceivedNSeparation++;
                    float rSquare = neighborSeparationDistance*neighborSeparationDistance;
                    float ratio = (rSquare - sqrDistance) / sqrDistance; //This ratio can help scale the separation force inversely
                    
                    boids[i].flockAverageSeparation -= distVec.normalize() * ratio; //We want the direction but not the magnitude of the distance between boids
                }
            }
        }
        
        // by computing this scalar factor we avoid dividing each component of flockCentroid vector
        if(boids[i].numPerceivedNCohesion > 0)
        {
            boids[i].perceivedNCohesionFactor = 1 / boids[i].numPerceivedNCohesion;
            boids[i].flockCentroid *= boids[i].perceivedNCohesionFactor;
        }
            
        if(boids[i].numPerceivedNAlignment > 0)
        {
            boids[i].perceivedNAlignmentFactor = 1 / boids[i].numPerceivedNAlignment;
            boids[i].flockAverageSeparation *= boids[i].perceivedNCohesionFactor;
        }
        
        //AVOIDANCE
        
        for(size_t v = 0; v < uniformGridRef->obstaclesIndexs.size(); v++)
        {
            ofVec3f obsPos = uniformGridRef->getObstaclePositionByIndex(v);
            //Offset becase the Voxel Mesh is rendered using the center of the cube
            obsPos.x += 50;
            obsPos.y += 50;
            obsPos.z -= 50;
            
            //Vector describing the distance from the obstacle to the boid, since we need it to move away
            ofVec3f distVec = boids[i].getPosition() - obsPos;
            
            //Euclidean distance to the obstacle
            float sqrDistance = distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z;
            
            float sqrThreshold = (obstacleAvoidanceDistance * obstacleAvoidanceDistance);
            
            if(sqrDistance < sqrThreshold)
            {
                float ratio = (sqrThreshold - sqrDistance) / sqrDistance;
                boids[i].obstaclesAverageAvoidance += distVec.normalize() * ratio;//;.normalize();
            }
        }
                
        boids[i].updateSteeringForces();
        boids[i].updatePositionInWorldGrid(*uniformGridRef);
    }
}
const std::vector<Boid> BoidsManager::getBoids() const
{
  return boids;
}
