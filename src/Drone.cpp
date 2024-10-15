//
//  Drone.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-15.
//
#pragma once
#include "Drone.hpp"

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


void Drone::update(const ofVec3f & newPosition, const ofVec3f & newOrientation)
{
    m_droneBodyMesh.setGlobalPosition(newPosition);
    m_raySensorMesh.setGlobalPosition(newPosition);
    
    m_raySensorMesh.lookAt(newPosition + newOrientation);
}

void Drone::draw()
{
    m_droneBodyMesh.drawWireframe();
    m_raySensorMesh.drawWireframe();
}
