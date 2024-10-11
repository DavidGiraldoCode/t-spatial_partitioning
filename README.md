# Spatial partitioning study - with C++ in OpenFrameworks

<img width="400" alt="image" src="https://github.com/user-attachments/assets/6c7df04e-a9f7-4cd7-aa70-b4b079645729">
<img width="400" alt="image" src="https://github.com/user-attachments/assets/963b99a4-e775-4128-b00f-f8a33ffb47a5">

# Build instructions
To run this project, first [Download OpenFrameworks source code](https://openframeworks.cc/download/). Then, move inside the `myApps` folder. You need this to have access to the OpenFrameworks header files.
```bash
cd openframeworks_version_####/apps/myApps/
git clone [URL]
```

## Main Backlog
- [ ] Add a member variable to store the boids count of a voxel and update it
- [ ] Enable boids to detect when a voxel in the field of view is FULL (is an obstacle)
- [ ] Implement voxelization of a mesh
- [ ] Implement Octree for mesh voxelization
- [x] Create a volume representing the domain of the environment
- [x] subdivide the volume into a uniform grid of voxels, visualize them
## Utilities Backlog
- [ ] Enable the grid to start at any point
- [ ] Enabled GUI to update the size of the width, height, and depth of the grid. Add update button
- [ ] Organize objects into scenes
- [ ] Add a vector displaying the direction of the boid
- [ ] Add point on MAX visibility distance in the head of the direction vector
- [ ] Implement Boids behaviours

## Algorithm to determine if a point is inside a voxel

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
