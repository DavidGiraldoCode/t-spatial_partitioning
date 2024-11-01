# Technical Challenges

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
