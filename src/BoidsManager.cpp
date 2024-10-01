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
                if(sqrDistance < (neighborCohesionDistance*neighborCohesionDistance))
                {
                    boids[i].numPerceivedNCohesion++;
                    boids[i].flockCentroid += boids[j].getPosition();
                }
                if(sqrDistance < (neighborAlignmentDistance*neighborAlignmentDistance))
                {
                    boids[i].numPerceivedNAlignment++;
                    boids[i].flockAverageAlignment += boids[j].velocity;
                }
                if(sqrDistance < (neighborSeparationDistance*neighborSeparationDistance))
                {
                    boids[i].numPerceivedNSeparation++;
                    float d = (boids[j].getPosition() - boids[i].getPosition()).length();
                    boids[i].flockAverageAvoidance += neighborSeparationDistance - d / d * boids[j].getPosition() - boids[i].getPosition();
                }
            }
        }
        // by computing this scalar factor we avoid dividing each component of flockCentroid vector
        if(boids[i].numPerceivedNCohesion > 0)
            boids[i].perceivedNCohesionFactor = 1 / boids[i].numPerceivedNCohesion;
        if(boids[i].numPerceivedNAlignment > 0)
            boids[i].perceivedNAlignmentFactor = 1 / boids[i].numPerceivedNAlignment;
        
        boids[i].updateSteeringForces();
        boids[i].updatePositionInWorldGrid(*uniformGridRef);
    }
}
const std::vector<Boid> BoidsManager::getBoids() const
{
  return boids;
}
