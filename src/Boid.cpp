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
    forward = ofVec3f(0,0,1);
    velocity = forward * 10.0f;//ofVec3f(0.0f, 1.0f, 0.0f);
    acceleration = ofVec3f(0.0f, 0.0f, 0.0f);
    boundingForce = ofVec3f(0.0f,0.0f,0.0f);
    
    speedConstrain = (ofVec3f(MAX_SPEED,MAX_SPEED,MAX_SPEED).length() - velocity.length()) * velocity.normalize();
    
    //TODO commented for the Naive Boids Scene
    //wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf());
    //wanderChange = (int)(200 * ofRandom(1.0f,10.0f));
    
   
    wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize();
    velocity += wanderDirection;
    velocity = velocity.normalize() * 2.0f;
    
    //NEW
    worldCenter = ofVec3f(x, y, z);
    
    cohesionForce       =   ofVec3f(0.0f, 0.0f, 0.0f);
    separationForce     =   ofVec3f(0.0f, 0.0f, 0.0f);
    alignmentForce      =   ofVec3f(0.0f, 0.0f, 0.0f);
}

Boid::Boid(const ofVec3f &spawnPosition)
{
    
    position = spawnPosition;
    forward = ofVec3f(0,0,1);
    acceleration = ofVec3f(0,0,0);
    
    //velocity = forward * MAX_SPEED;
    
    std::cout << velocity << " velocity\n";
    wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize();
    velocity = wanderDirection * MAX_SPEED;
    std::cout << velocity << " velocity\n";
    //velocity = velocity.normalize() * MAX_SPEED;
    
    //NEW
    worldCenter = spawnPosition;
}

Boid::Boid(const Boid& other)
{
    position = other.position;
    velocity = other.velocity;
    forward = other.forward;
    worldCenter = other.worldCenter;
    
    SEPARATION_FACTOR = other.SEPARATION_FACTOR;
    COHESION_FACTOR = other.COHESION_FACTOR;
    ALIGNMENT_FACTOR = other.ALIGNMENT_FACTOR;
    
    cohesionForce = other.cohesionForce;
    separationForce = other.separationForce;
    alignmentForce = other.alignmentForce;
    
    numPerceivedNCohesion = other.numPerceivedNCohesion;
    numPerceivedNAlignment = other.numPerceivedNAlignment;
    numPerceivedNSeparation = other.numPerceivedNAlignment;
    
}

Boid::~Boid()
{
    //std::cout << "Good by Boid \n";
}

void Boid::move()
{
   // dampingVelocity();
    //std::cout <<  ofGetElapsedTimef() << '\n';
    //std::cout <<  ofGetElapsedTimeMillis() << '\n';
    //acceleration = ofVec3f(0.0f, 0.0f, 0.0f);
    
    
    if(wanderCounter >= wanderChange)
    {
        //wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf());
        //wanderDirection = wanderDirection.normalize() * velocity.length();
       // wanderCounter = 0;
    }
    
    //wanderCounter++;
    
    //std::cout << wanderCounter <<"wanderCounter updated\n";
    //std::cout << wanderDirection <<"wanderDirection updated\n";
    
    //acceleration = acceleration + wanderDirection + speedConstrain + boundingForce;//.normalize();
    
    //velocity = velocity + acceleration * 0.01f;
    //velocity = velocity + wanderDirection + boundingForce;// * 0.001f;
    
    //position = position + velocity;
    
//    std::cout << "acceleration magnitud [ "<< acceleration.length() << "] \n";
//    std::cout << "velocity [ "<< velocity << "] \n";
//    std::cout << "position [ "
//    << "x: " << position.x
//    << ", y: " << position.y
//    << ", z: " << position.z << "] \n";
}

void Boid::updateSteeringForces()
{
    //reset the acceleration at the begging of the simulation step
    acceleration.x = 0.0f;
    acceleration.y = 0.0f;
    acceleration.z = 0.0f;
    
    velocity = sphericalBoundaryForce(); //GOOD enough solution for now
     
    
    if(numPerceivedNCohesion > 0)
        cohesionForce =  (flockCentroid - position).normalize() * COHESION_FACTOR;
    
    if(numPerceivedNAlignment > 0)
        alignmentForce =  (flockAverageAlignment - velocity).normalize() * ALIGNMENT_FACTOR;

    if(numPerceivedNSeparation > 0)
        separationForce = flockAverageSeparation * SEPARATION_FACTOR;
    
    acceleration += cohesionForce;
    acceleration += alignmentForce;
    acceleration += separationForce;
    
    velocity += acceleration;
    position += velocity * ofGetLastFrameTime();
    
    //Reset N count
    numPerceivedNCohesion = 0;
    numPerceivedNAlignment = 0;
    numPerceivedNSeparation = 0;
}

ofVec3f& Boid::sphericalBoundaryForce()
{
    float boundaryRadius = 1000.0f;
    if(worldCenter.distance(position) < boundaryRadius) return velocity;
    
    wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize() * (boundaryRadius * 0.5f); //Compute random direction, then scale it by half of the boundary
    ofVec3f randomPointInsideSphere = worldCenter + wanderDirection; // Added to the position of the world so it is now a point inside the sphere
    ofVec3f newDirection = (randomPointInsideSphere - position).normalize() * MAX_SPEED; // Calculate a new direction towards the random point inside the sphere
    
    velocity = newDirection;
    
    return velocity;
}

const ofVec3f& Boid::getPosition() const
{
    return position;
}
const ofVec3f& Boid::getVelocity() const
{
    return velocity;
}

const ofVec3f Boid::getDirection() //Check is this could be memory leak
{
    return velocity.getNormalized();
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
    
    boundingForce = (boundingAreaCenter - position);
    
    if(isWithinBoundaries)
        boundingForce *= 0.000001f;
    else
        boundingForce *= 0.001f;
    
//    if(isWithinBoundaries)
//        boundingForce = ofVec3f(0.0f,0.0f,0.0f);
//    else
//        boundingForce = (boundingAreaCenter - position);
    
    //boundingForce *= 0.05f; //scale factor, so the force is not too strong
    //boundingForce = boundingForce.normalize() * MAX_SPEED; //scale factor, so the force is not too strong

    //std::cout << boundingForce <<"Bounding force updated\n";
}

void Boid::dampingVelocity()
{
    //speedConstrain = (ofVec3f(0.0f,0.0f,MAX_SPEED).length() - velocity.length()) * velocity.normalize();
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

/*
 Everything related to the grid
 */

void Boid::updatePositionInWorldGrid(UniformGrid & uniformGrid)
{
    int newPosition = uniformGrid.isPointInsideAVoxel(position);
    if(currentPositionInGrid == newPosition)
    {
        previousPositionInGrid = currentPositionInGrid;
        return;
    }; //We have not moved to another voxel, do nothing
    
    currentPositionInGrid = newPosition; //We have indeed change to another place
    
    if(currentPositionInGrid != -1) // We are still inside the grid, so notify the new voxel
        uniformGrid.addObjectToVoxel(currentPositionInGrid);
    
    if(previousPositionInGrid != -1) //The boid was not outside, notify previous voxel
        uniformGrid.removeObjectFromVoxel(previousPositionInGrid);
    
    previousPositionInGrid = currentPositionInGrid; //Update position.
}
