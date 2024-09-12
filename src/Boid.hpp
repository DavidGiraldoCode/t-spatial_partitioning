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
#include "ofUtils.h"

class Boid
{
public:
    /**The default constructor allows for proper memory allocation and stroing class in std containers**/
    Boid() :
        position(0.0f, 0.0f, 0.0f),
        velocity(0.0f, 0.0f, 0.0f),
        acceleration(0.0f, 0.0f, 0.0f){};
    Boid(float x, float y, float z);
    
    //copy and move construc
    ~Boid();
    void move();
    void applyBoundingForce(const ofVec3f & boundingAreaCenter, float width, float height, float depth);
    const ofVec3f getPosition();
private:
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f acceleration;
    ofVec3f wanderDirection;
    ofVec3f boundingForce;
    ofVec3f speedConstrain;
    int wanderCounter = 0;
    int wanderChange = 0;
    float MAX_SPEED = 20.0f;
    void dampingVelocity();
};

