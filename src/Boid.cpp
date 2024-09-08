//
//  Boid.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-08.
//

#include "Boid.hpp"

Boid::Boid(float x, float y, float z)
{
    position = ofVec3f(x, y, z);
    velocity = ofVec3f(0.0f, 1.0f, 0.0f);
    acceleration = ofVec3f(0.0f, 0.0f, 0.0f);
    boundingForce = ofVec3f(0.0f,0.0f,0.0f);
    
    speedConstrain = (ofVec3f(MAX_SPEED,MAX_SPEED,MAX_SPEED).length() - velocity.length()) * velocity.normalize();
    wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf());
}

Boid::~Boid()
{
    //std::cout << "Good by Boid \n";
}

void Boid::move()
{
    dampingVelocity();
    //std::cout <<  ofGetElapsedTimef() << '\n';
    //std::cout <<  ofGetElapsedTimeMillis() << '\n';
    acceleration = ofVec3f(0.0f, 0.0f, 0.0f);
    
    
    if(wanderCounter >= 200)
    {
        wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf());
        wanderCounter = 0;
    }
    
    wanderCounter++;
       
    
    wanderDirection = wanderDirection.normalize() * velocity.length();
    
    //std::cout << wanderCounter <<"wanderCounter updated\n";
    //std::cout << wanderDirection <<"wanderDirection updated\n";
    
    acceleration = acceleration + wanderDirection + speedConstrain + boundingForce;//.normalize();
    
    velocity = velocity + acceleration * 0.01f;
    
    position = position + velocity;
    
//    std::cout << "acceleration magnitud [ "<< acceleration.length() << "] \n";
//    std::cout << "velocity [ "<< velocity << "] \n";
//    std::cout << "position [ "
//    << "x: " << position.x
//    << ", y: " << position.y
//    << ", z: " << position.z << "] \n";
}

const ofVec3f Boid::getPosition()
{
    return position;
}


void Boid::applyBoundingForce(const ofVec3f & boundingAreaCenter, float width, float height, float depth)
{
    /**
     This checks if the position of the boid is inisde the limits of the bounding volume
     It need to be <= >= othewise when the boid is right in the same position of the bounding box, it yields as is not within boundaries.
     **/
    bool isWithinBoundaries =
    boundingForce.x - (width/2)  <= position.x &&
    boundingForce.y - (height/2) <= position.y &&
    boundingForce.z - (depth/2)  <= position.z &&
    
    boundingForce.x + (width/2)  >= position.x &&
    boundingForce.y + (height/2) >= position.y &&
    boundingForce.z + (depth/2)  >= position.z;
    
    if(isWithinBoundaries)
        boundingForce = ofVec3f(0.0f,0.0f,0.0f);
    else
        boundingForce = (boundingAreaCenter - position);
    
    //boundingForce *= 0.25f; //scale factor, so the force is not too strong

    //std::cout << boundingForce <<"Bounding force updated\n";
}

void Boid::dampingVelocity()
{
    speedConstrain = (ofVec3f(MAX_SPEED,MAX_SPEED,MAX_SPEED).length() - velocity.length()) * velocity.normalize();
}
/*
 std::cout
         << "width: " << width
         << " - height: " << height
         << " - depth: " << depth
                 <<"\n";
 
 
 std::cout
 << "boundingAreaCenter.x: " << boundingAreaCenter.x
 << "boundingAreaCenter.y: " << boundingAreaCenter.y
 << "boundingAreaCenter.z: " << boundingAreaCenter.z
         <<"\n";
 
 std::cout <<
 (boundingForce.x - (width/2)  <= position.x) << " " <<
 (boundingForce.y - (height/2) <= position.y) << " " <<
 (boundingForce.z - (depth/2)  <= position.z) << " " <<
 
 (boundingForce.x + (width/2)  >= position.x) << " " <<
 (boundingForce.y + (height/2) >= position.y) << " " <<
 (boundingForce.z + (depth/2)  >= position.z) << '\n';
 
 
 std::cout<<"isWithinBoundaries: "<<isWithinBoundaries<<'\n';
 */
