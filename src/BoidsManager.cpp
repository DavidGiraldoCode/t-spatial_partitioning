//
//  BoidsManager.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
#include "BoidsManager.hpp"

BoidsManager::BoidsManager(const ofVec3f &spawnPoint, int BOIDS_COUNT, UniformGrid *uniformGrid)
{
    uniformGridRef = uniformGrid;
    //Instantiating the Boids in the center of the bounding volume
    for(size_t i = 0; i < BOIDS_COUNT; i++)
    {
        boids.push_back(Boid(spawnPoint));
    }
    std::cout<<neighborCohesionDistance << ' '
    <<neighborSeparationDistance << ' '
    <<neighborAlignmentDistance
    <<'\n';
}
BoidsManager::~BoidsManager()
{
            
}
                        
void BoidsManager::updateSteeringForces()
{
    for(size_t i = 0; i < boids.size(); i++)
    {
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
                    
                    boids[i].flockAverageSeparation += ratio * distVec.normalize(); //We want the direction but not the magnitude of the distance between boids
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
        
        boids[i].updateSteeringForces();
        //boids[i].updatePositionInWorldGrid(*uniformGridRef);
    }
}
const std::vector<Boid> BoidsManager::getBoids() const
{
  return boids;
}
