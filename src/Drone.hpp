//
//  Drone.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-14.
//

#pragma once
#include <stdio.h>
#include "of3dPrimitives.h"

// 4 duplicated symbols error
/// This happend because the methods were being define here aswell, so other translations units ended up with their own copies of the definitions, solution, keep good practices, use .cpp

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
    
    void updateD(const ofVec3f & newPosition);
    void drawD();
    
private:
    ofSpherePrimitive       m_droneBodyMesh;
    of3dPrimitive           m_raySensorMesh;
};
