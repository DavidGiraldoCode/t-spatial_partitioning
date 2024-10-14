//
//  Drone.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-14.
//

#pragma once
#include <stdio.h>
#include "of3dPrimitives.h"

class Drone
{
public:
    /**
     If Drone takes an EnhancedBoid reference as an argument, the compiler cannot create a Drone object without that reference.
     EnhancedBoid & boidBrain, and that is why is better to decouple this logic and leave only rendering responsabilitiies to this class
     **/
    
    Drone() = default;
    Drone(const ofVec3f & spawnPosition);
    
    //Drone(const Drone &other) = delete;  // Prevent copying
    //Drone & operator=(const Drone &other) = delete;  // Prevent assignment

    //Drone(Drone &&other) = default;  // Allow move construction
    //Drone & operator=(Drone &&other) = default;  // Allow move assignment

    /// If the class doesn't dynamically allocate memory or handles file, the default destructor will suffice.
    ~Drone() = default;
    
    void update(const ofVec3f & newPosition);
    void draw();
    
private:
    ofSpherePrimitive       m_droneBodyMesh;
    of3dPrimitive           m_raySensorMesh;
};

Drone::Drone(const ofVec3f & spawnPosition)
{
   
    //The ray mesh needs to be define in local space.
    m_raySensorMesh.getMesh().addVertex(ofVec3f(-2,0,0));
    m_raySensorMesh.getMesh().addVertex(ofVec3f(0,0, -800));
    m_raySensorMesh.getMesh().addVertex(ofVec3f(2,0,0));
    m_raySensorMesh.getMesh().setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    m_droneBodyMesh.setGlobalPosition(spawnPosition);
    m_raySensorMesh.setGlobalPosition(spawnPosition);
}


void Drone::update(const ofVec3f & newPosition)
{
    m_droneBodyMesh.setGlobalPosition(newPosition);
    m_raySensorMesh.setGlobalPosition(newPosition);
}

void Drone::draw()
{
    m_droneBodyMesh.drawWireframe();
    m_raySensorMesh.drawWireframe();
}
