//
//  Boid.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-08.
//

#pragma once
#include <stdio.h>
#include "ofVec3f.h"
#include "ofMath.h"
#include <cmath>
#include "ofUtils.h"
#include "UniformGrid.hpp"
#include "ofAppRunner.h"

class Boid
{
public:
    /**The default constructor allows for proper memory allocation and stroing class in std containers**/
    Boid() :
        position(0.0f, 0.0f, 0.0f),
        velocity(0.0f, 0.0f, 0.0f),
        acceleration(0.0f, 0.0f, 0.0f){};
    Boid(float x, float y, float z);
    Boid(const Boid& other);
    
    /**
     * Spawn the boid in a given spawn position.
     * @param spawnPosition is a vector representing the position
     * @param hasRandomDirection enables a random direction once it is spawned, if false it will go along in the Z axis.
     */
    Boid(const ofVec3f &spawnPosition, bool hasRandomDirection = true);
    //copy and move construc
    ~Boid();
            void        move();
            void        applyBoundingForce(const ofVec3f & boundingAreaCenter, float width, float height, float depth);
    const   ofVec3f&    getPosition() const;
    const   ofVec3f     getDirection();
    const   ofVec3f&    getVelocity() const;
            void        updatePositionInWorldGrid(UniformGrid & uniformGrid);
            void        updateSteeringForces();
    
    // Avoidance
    /**
     * Signals the boid to take evasive maneuvers
     */
            void        activateAvoidanceProtocol();
    /**
     * Signals the boid to stop evasive maneuvers
     */
            void        deactivateAvoidanceProtocol();
    
    /**
     * Creates an spherical boundary that make the boid change direction once it reaches the surface of the sphere from the inside
     * @note This is for testing and prototyping purposes
     */
            ofVec3f&    sphericalBoundaryForce();
    
    //Steering forces
            ofVec3f     flockCentroid;
            ofVec3f     flockAverageAlignment;
            ofVec3f     flockAverageSeparation;//TODO change name, is not average
    
            ofVec3f     obstaclesAverageAvoidance;
    
            ofVec3f     cohesionForce;
            ofVec3f     alignmentForce;
            ofVec3f     separationForce;
    
            ofVec3f     avoidanceForce;
    
            float       numPerceivedNCohesion = 0;
            float       numPerceivedNAlignment = 0;
            float       numPerceivedNSeparation = 0;
    
            float       perceivedNCohesionFactor = 0;
            float       perceivedNAlignmentFactor = 0;
            float       perceivedNSeparationFactor = 0;
    
            ofVec3f     velocity;
            ofVec3f     position;
    

            float   COHESION_FACTOR     ;//=   2.0f;
            float   ALIGNMENT_FACTOR    ;//=   2.0f;
            float   SEPARATION_FACTOR   ;//=   10.0f;
            float   AVOIDANCE_FACTOR   ;
private:
    
    ofVec3f forward;
    
    ofVec3f acceleration;
    ofVec3f wanderDirection;
    ofVec3f boundingForce;
    ofVec3f speedConstrain;
    
    //
    int currentPositionInGrid = -1;
    int previousPositionInGrid = -1;
    int wanderCounter = 0;
    int wanderChange = 0;
    //Steering forces
    float   MAX_SPEED           =     200.0f;
    
    // Avoidance
    bool obstacleDetected = false;

    
    
    //
    void dampingVelocity();
    
    //NEW
    ofVec3f worldCenter;
};

