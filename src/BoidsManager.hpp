//
//  BoidsManager.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
//  In a naive appproach, traverse the boids to compute averages
//
#include "Boid.hpp"
#include "UniformGrid.hpp"

class BoidsManager
{
public:
    BoidsManager(){};
    BoidsManager(const ofVec3f &spawnPoint, int BOIDS_COUNT, UniformGrid* uniformGridRef);
    ~BoidsManager();
    
            void                updateSteeringForces();
    const   std::vector<Boid>   getBoids() const; //For passing the values to the mesh
            UniformGrid*        uniformGridRef = nullptr;
    // Steering forces settings
            float               neighborCohesionDistance    =   200;
            float               neighborSeparationDistance  =   100;
            float               neighborAlignmentDistance   =   100;
    
            float               MAX_SPEED                   =   200.0f;
            
            float               COHESION_FACTOR             =   2.0f;
            float               ALIGNMENT_FACTOR            =   2.0f;
            float               SEPARATION_FACTOR           =   5.0f;
    
private:
    std::vector<Boid>  boids = {};

};
