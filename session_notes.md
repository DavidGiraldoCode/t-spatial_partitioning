# Session notes (Oldest first )

## Session 2024-10-29: An Obstacle Avoidance Equation

### Objective
**Study and understand an equation for obstacle avoidance.**

I found a simple and "stable" equation for dodging behavior proposed by Ma and Chou (2024). Their paper addresses stability issues in multi-agent simulations (MAS) and proposes an equation to solve the minima problem. They created a *Rotation Operator* vector that pulls the agent away from the obstacle center based on the angle between the agent's velocity vector and the agent-to-obstacle vector.

Using this approach, the objective is to enable an agent to dodge an obstacle directly in front.

---

### What's the Minima Problem?
When an agent in a simulation cannot resolve conflicting forces (e.g., collision avoidance, target following, obstacle avoidance) in a direction that would allow it to exit from a concave shape, it may get trapped or stop. This often happens in navigation simulations when the agents lack prior environmental knowledge, meaning a pathfinding algorithm is not feasible.

---

### Breaking Down the Rotation Operator

#### Variables:
- **Obstacle Center**: Position of the obstacle.
- **Agent Position**: Current position of the agent.
- **Agent Velocity**: Agent's directional movement vector.
- **Critical Radius**: Distance threshold to initiate avoidance behavior.

#### Steps:
1. **Distance Check**: Validate if the agent-to-obstacle distance is equal to or less than the Critical radius.
2. **Angle Comparison**:
   - Normalize both vectors: `"a"` (agent's velocity) and `"ao"` (agent-to-obstacle).
   - Ignore the Z component (UP) since this is a 2D rotation.
   - Compute a simplified cross-product to obtain the sign, indicating left or right orientation.
3. **Compute Rotation Components**:
   - **Radial Attenuation**: Inverse relationship with the agent's distance from the obstacle, dampening rotation force as the agent moves away.
   - **Rotation Velocity and Proximity Damping**: Increases velocity force as proximity increases, providing a smooth transition.
   - **Amplitude Coefficient**: A user-defined value to scale the rotation operator's effect.

#### Ma and Chou's Rotation Operator Equation
> ![DESMOS PICTURE]

---

### Next Steps
- **Implement in Code**: Outline steps for adding the rotation operator.
- **Voxel-based Setup Compatibility**: Assess how this fits with a voxel-based obstacle detection setup.

---

## Session 2024-10-29: Rotation Operator Brute Force Implementation

### Objective
**Make a Boid move forward while dodging an obstacle in front using Ma and Chou's Rotation Operator.**

1. Initialized the boid within a voxel, moving forward.
2. Set up a hard-coded intersection point as the obstacle.

### Findings
- The Boid successfully avoided obstacles, but turns were minimal; adjusting the amplitude coefficient had a significant effect.
- Modified the attenuation function to use linear distance instead of squared distance.
- Functionality verified from both left and right approaches.

---

### Next Steps
- **Dynamic Obstacle Positioning**: Test how the rotation operator functions with real-time updates in obstacle positions.
- **Multiple Obstacles**: Experiment with handling multiple obstacles simultaneously.
- **New Obstacle Detection**: Determine if the agent should track several obstacles in the critical zone, similar to neighbor tracking.

---

[1] X. Ma and T. Chou, "Practical time-varying formation cooperative control for high-order nonlinear multi-agent systems avoiding spatial resource conflict via safety constraints," *International Journal of Robust and Nonlinear Control*, vol. n/a, no. n/a, doi: 10.1002/rnc.7600.

--- 

## On Spatial queries in 1D and 3D

Algorithm to determine if a point is inside a voxel

```C++
const  int UniformGrid::isPointInsideAVoxelGivenRayDirection(const ofVec3f &pointQuery, const ofVec3f & planeNormal ,const ofVec3f &rayDirection) const
{
    //Casting values and de-scaling the world position to units and increments of 1
    float pX = floor(pointQuery.x * m_normalizeSizeFactor); // m_normalizeSizeFactor = 1/m_voxelSize;
    float pY = floor(pointQuery.y * m_normalizeSizeFactor);
    float pZ = floor((pointQuery.z * -1) * m_normalizeSizeFactor);// Recall that we have defined the depth of the grid to be far away from the camera
    
    /*Checking directions*/
    if (planeNormal.x != 0)
    {
        if (rayDirection.x < 0) // if the Ray is pointing in the opposite direction as the world X Normal
            pX -= 1; // The Voxel is hitting is not from [0 -> width] but [width -> 0]
    }
    
    if (planeNormal.y != 0)
    {
        if (rayDirection.y < 0) // if the Ray is pointing in the opposite direction as the world Y Normal
            pY -= 1; // The Voxel is hitting is not from [0 -> height] but [height -> 0]
    }
    
    
    if (planeNormal.z != 0) // If we are evaluating the Z axis
    {
        if(rayDirection.z > 0) // if the Ray is pointing in the same direction as the world Z Normal
            pZ -= 1; // The Voxel is hitting is not from [0 -> depth] but [depth -> 0]
    }
    
    bool inColsBounds   = pX >= 0 && pX < m_nCols;
    bool inRowsBounds   = pY >= 0 && pY < m_nRows;
    bool inLayersBounds = pZ >= 0 && pZ < m_nLayers;
    
    if(!inColsBounds || !inRowsBounds || !inLayersBounds)
        return -1;

    int indexInOneD = (int)pZ * m_nCols * m_nRows + (int)pY * m_nCols + (int)pX;
    
    if(indexInOneD < 0 || indexInOneD >= voxels.size())
        return -1;

    return indexInOneD;
}
```

## Useful snipets
```C++
    stringstream ss;
    ss << "Spatial partitioning: " << '\n' << '\n';
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) << '\n' ;
    ss << "Voxel Grid Resolution: " << voxelGridResolution << '\n' ;
    ofDrawBitmapStringHighlight(ss.str().c_str(), 20, 20);
```