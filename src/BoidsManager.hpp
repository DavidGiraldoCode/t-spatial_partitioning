//
//  BoidsManager.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
//  In a naive appproach, traverse the boids to compute averages
//
#pragma once
#include "Boid.hpp"
#include "UniformGrid.hpp"

class BoidsManager
{
public:
    BoidsManager(){};
    /**
     * Constructs a BoidsManager object. This constructor initializes the boid swarm at a specific spawn point
     * within the 3D environment, based on the number of boids specified.
     * @param spawnPoint The position to spawn the boids.
     * @param BOIDS_COUNT The number of boids to spawn.
     * @param uniformGridRef A pointer to the Uniform grid.
     */
    BoidsManager(const ofVec3f &spawnPoint, int BOIDS_COUNT, UniformGrid* uniformGridRef);
    ~BoidsManager() = default;
    
    /**
     * Updates the steering forces (separation, cohesion and alignment) for all the boid by iterating in i and j. Also compute boid-like obstacle avoidance.
     * It calls `updateSteeringForces` on each boid.
     * @note Complexity O(n^2)
     */
            void                updateSteeringForces();
    const   std::vector<Boid>   getBoids() const; //For passing the values to the mesh
            UniformGrid*        uniformGridRef = nullptr;
    // Steering forces settings
            float               neighborCohesionDistance    =   200;
            float               neighborSeparationDistance  =   100;
            float               neighborAlignmentDistance   =   100;
    
            float               obstacleAvoidanceDistance   =   300;
    
            float               MAX_SPEED                   =   200.0f;
            
            float               COHESION_FACTOR             =   2.0f;
            float               ALIGNMENT_FACTOR            =   2.0f;
            float               SEPARATION_FACTOR           =   4.0f;
            float               AVOIDANCE_FACTOR            =   4.0f;
    
private:
    std::vector<Boid>  boids;

};
