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
    avoidanceForce      =   ofVec3f(0.0f, 0.0f, 0.0f);
}

Boid::Boid(const ofVec3f &spawnPosition, bool hasRandomDirection)
{
    
    position = spawnPosition;
    forward = ofVec3f(0,0,1);
    acceleration = ofVec3f(0,0,0);
    
    //velocity = forward * MAX_SPEED;
    
    //std::cout << velocity << " velocity\n";
    if(hasRandomDirection)
    {
        wanderDirection = ofVec3f(ofRandomf(), ofRandomf(), ofRandomf()).normalize();
        velocity = wanderDirection * MAX_SPEED;
    }
    else
    {
        velocity = ofVec3f(0,0,-1) * MAX_SPEED;
    }
    //std::cout << velocity << " velocity\n";
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
    AVOIDANCE_FACTOR = other.AVOIDANCE_FACTOR;
    
    cohesionForce = other.cohesionForce;
    separationForce = other.separationForce;
    alignmentForce = other.alignmentForce;
    
    numPerceivedNCohesion = other.numPerceivedNCohesion;
    numPerceivedNAlignment = other.numPerceivedNAlignment;
    numPerceivedNSeparation = other.numPerceivedNAlignment;
    
    //obstacleDetected = other.obstacleDetected;
    
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

/**
 * Updates the forces on the boid, gets call from the class `BoidManager`.
 * @note This will be re-factor, as in further version, the boid will get it neighbours spatially hashed
 */
void Boid::updateSteeringForces()
{
    //reset the acceleration at the begging of the simulation step
    acceleration.x = 0.0f;
    acceleration.y = 0.0f;
    acceleration.z = 0.0f;
    
    //velocity = sphericalBoundaryForce(); //GOOD enough solution for now
     
    
    if(numPerceivedNCohesion > 0)
        cohesionForce =  (flockCentroid - position).normalize() * COHESION_FACTOR;
    
    if(numPerceivedNAlignment > 0)
        alignmentForce =  (flockAverageAlignment - velocity).normalize() * ALIGNMENT_FACTOR;

    if(numPerceivedNSeparation > 0)
        separationForce = flockAverageSeparation * SEPARATION_FACTOR;
    
    //BOID-LIKE obstacle avoidance
    //avoidanceForce = obstaclesAverageAvoidance.normalize() * AVOIDANCE_FACTOR;
    
    acceleration += cohesionForce;
    acceleration += alignmentForce;
    acceleration += separationForce;
    
    //acceleration += avoidanceForce;
    /* 🚧 Obstacle avoidance logic, simple rotation
    std::cout << obstacleDetected << " obstacleDetected\n";
    if(obstacleDetected)
    {
        float angle = -(glm::pi<float>()/2);
        // Applying a rotation matrix equation with respect to y
        float x = (velocity.x * cos(angle)) + (velocity.z * sin(angle));
        float z = (velocity.x * (-sin(angle))) + (velocity.z * cos(angle));
        
        ofVec3f rightAvoidanceV = ofVec3f(x, velocity.y, z);
        float avoidanceFore = 0.006f;
        acceleration += (rightAvoidanceV * avoidanceFore);
        std::cout << rightAvoidanceV << " \n";
        COHESION_FACTOR = 0.001f;
        ALIGNMENT_FACTOR = 0.001f;
        SEPARATION_FACTOR = 0.001f;
    }
    */
    
    // Ma and Chou Rotator Operator
    obstacle = ofVec3f(910,950, -2000);
    //ofVec3f(950,980, -2000); // The obstacle is slightly to the right
    ofVec3f boidToObstacle = obstacle - position;
    ofVec3f obstacleToBoid = boidToObstacle * -1;
    // Critical radius
    float criticalRadius = 800.0f; // Ideally half the reach of the visibility, ray reach.
    float distanceToObstacle = boidToObstacle.length();
    if(distanceToObstacle <= criticalRadius /*obstacleDetected*/)
    {
        
        
        
        // Simple Cross product, taking Y as Up vector, with contribution zero.
        float obstacleLocation = (velocity.normalize().x * boidToObstacle.normalize().z)
                                - (velocity.normalize().z * boidToObstacle.normalize().x);
        
        ofVec3f rotatorVelocity = ofVec3f(0.0f, 0.0f, 0.0f);
        const float overflowThreshold = 9999.0f;
        
        if(obstacleLocation < -overflowThreshold)
            obstacleLocation = -overflowThreshold;
        else if(obstacleLocation > overflowThreshold)
            obstacleLocation = overflowThreshold;

        std::cout << obstacleLocation << " obstacleLocation\n";
        
        // If obstacleLocation > 0 the obstacle is to the left, we reflect to the right
        if(obstacleLocation < 0)
        {
            //std::cout << " to the left\n";
            rotatorVelocity.x = obstacleToBoid.z;
            rotatorVelocity.z = -obstacleToBoid.x;
        }
        else if(obstacleLocation >= 0) // If obstacleLocation <= 0 the obstacle is to the rigth, we refelct to the left
        {
            //std::cout << " to the right\n";
            rotatorVelocity.x = -obstacleToBoid.z;
            rotatorVelocity.z = obstacleToBoid.x;
        }
        std::cout << rotatorVelocity << " rotatorVelocity\n";
        
        
        float amplitudCoefficient = 50000.0f; // This is user defined, and is to make the operator stronger
        
        // Compute the radial attenuation function to the closer it gets, the stronger the avoidance rotation.
        float radialAttenuation = (1.0f / distanceToObstacle) - (1.0f / criticalRadius);
        // The radialAttenuation is getting value of 1.35573e-05
//        if(radialAttenuation < -overflowThreshold)
//            radialAttenuation = -overflowThreshold;
//        else if(radialAttenuation > overflowThreshold)
//            radialAttenuation = overflowThreshold;
        
        std::cout << radialAttenuation << " radialAttenuation\n";
        /**
         term acts as a proximity-based and velocity-aware scaling factor that ensures the avoidance maneuver is effective and natural
         r Squaring the distance indicates that the avoidance force decreases rapidly as the agent moves farther from the obstacle
         Dividing by 𝑉rotMagnitud scales down the effect when the agent moves faster, which is common in collision avoidance systems to prevent abrupt, unnatural-looking changes in direction at higher speeds.
         */
        // The original uses the squareDistanceToObstacle
        float squareDistanceToObstacle = (boidToObstacle.x * boidToObstacle.x) + (boidToObstacle.y * boidToObstacle.y) + (boidToObstacle.z * boidToObstacle.z);
        
        // Here I am using the euclian distance
        float velocityAndProximityDamping = 1.0f / (boidToObstacle.length() * rotatorVelocity.length());
        
        //Original;
        ofVec3f rotatorOperator = amplitudCoefficient * velocityAndProximityDamping * radialAttenuation * rotatorVelocity;
        
        acceleration += rotatorOperator;
        
        acceleration += ofVec3f(0.0f, 0.0f, -1.0f) * MAX_SPEED;
        //std::cout << rotatorOperator << " rotatorOperator\n";
    }
    else
    {
        acceleration += ofVec3f(0.0f, 0.0f, -1.0f) * MAX_SPEED;
    }
    
    //force the moving forwad;
//    ofVec3f forward = ofVec3f(0.0f, 0.0f, -1.0f) * MAX_SPEED;
//    velocity += forward;
    
    velocity += acceleration;
    
    if(velocity.length() > MAX_SPEED)
        velocity = velocity.normalize() * MAX_SPEED;
    
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

// Avoidance

void Boid::activateAvoidanceProtocol(const ofVec3f& obstaclePoint)
{
    
    //obstacle = obstaclePoint;
    obstacleDetected = true;
}

void Boid::deactivateAvoidanceProtocol()
{
    //std::cout << "obstacleDetected\n";
    obstacleDetected = false;
}
