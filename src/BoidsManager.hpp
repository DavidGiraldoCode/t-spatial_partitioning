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
private:
    std::vector<Boid>  boids = {};
    
    // Steering forces settings
    float neighborCohesionDistance = 100;
    float neighborSeparationDistance = 10;
    float neighborAlignmentDistance = 50;
};
