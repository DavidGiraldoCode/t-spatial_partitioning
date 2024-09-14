# Spatial partitioning study - with OpenFrameworks

To run this project, first [Download OpenFrameworks source code](https://openframeworks.cc/download/). Then, move inside the `myApps` folder. You need this to have access to the OpenFrameworks header files.
```bash
cd openframeworks_version_####/apps/myApps/
git clone [URL]
```

# Backlog
- [ ] Oranize objects into scenes
- [ ] Create volume representing the domain of the environment
- [ ] subdivide the volume into a uniform grid of voxels, visualize them  


## Useful snipets
```C++
    stringstream ss;
    ss << "Spatial partitioning: " << '\n' << '\n';
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) << '\n' ;
    ss << "Voxel Grid Resolution: " << voxelGridResolution << '\n' ;
    ofDrawBitmapStringHighlight(ss.str().c_str(), 20, 20);
```

## Algorithm to determine if a point is inside a voxel

```C++
bool UniformGrid::isPointInsideAVoxel(const ofVec3f &pointQuery)
{
    bool result = true;
    std::cout << "Cursor Position: " << pointQuery << '\n';
    //Casting values and de-scaling the world position to units and increments of 1
    int pX = floor(pointQuery.x / m_voxelSize);
    int pY = floor(pointQuery.y / m_voxelSize);
    int pZ = (floor(pointQuery.z / m_voxelSize) * -1) -1; //Recall that we hace define the deepth of the grid to be far away from the camera
    std::cout << "pX: " << pX << " pY: " << pY << " pZ: " << pZ << '\n';
    
    bool inColsBounds = pX >= 0 && pX < m_nCols;
    bool inRowsBounds = pY >= 0 && pY < m_nRows;
    bool inLayersBounds = pZ >= 0 && pZ < m_nLayers;
    
    std::cout << "Boundings X Y Z: " << inColsBounds << inRowsBounds << inLayersBounds << '\n';
    
    if(!inColsBounds || !inRowsBounds || !inLayersBounds)
    {
        std::cout << "Boid is outside the grid by Bounding checks" << '\n';
        return false;
    }

    int indexInOneD = pZ * m_nCols * m_nRows + pY * m_nCols + pX;
    std::cout << "indexInOneD: " << indexInOneD << '\n';
    
    if(indexInOneD < 0 || indexInOneD >= voxels.size())
    {
        std::cout << "Boid is outside the grid" << '\n';
        return false;
    }
    
    std::cout << "Boid is at voxel["<< indexInOneD <<"] : "<<voxels[indexInOneD].position << '\n';
    return true;
}
```