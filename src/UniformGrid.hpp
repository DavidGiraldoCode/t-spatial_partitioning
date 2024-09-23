//
//  UniformGrid.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-04.
//

#pragma once
#include <stdio.h>
#include "ofVec3f.h"

class UniformGrid
{
public:
    UniformGrid(){};
    UniformGrid(size_t nx, size_t ny, size_t nz, ofVec3f minPoint, ofVec3f maxPoint);
    UniformGrid(size_t width, size_t height, size_t depth, ofVec3f pivot, float VOXEL_SIZE);
    /*Constructor of a uniform grid with cell origin on the bottom left front [0,0,0] corner*/
    UniformGrid(size_t width, size_t height, size_t depth, float VOXEL_SIZE);
    ~UniformGrid();
           void          getVoxelByWorldCoordinates(const ofVec3f &point);
           void          getVoxelByIndex(size_t index);
           ofVec3f       getVoxelPositionByIndex(size_t index);
    const  size_t        getGridSize();
    const  int           isPointInsideAVoxel(const ofVec3f &pointQuery) const;
           void          removeObjectFromVoxel(int i);
           void          addObjectToVoxel(int i);
    const  int           getVoxelState(int i) const;
    const  int           getVoxelObstacle(int i) const; //TODO this should be state instead
private:
    struct Voxel // Bucket in Rynolds PS3 approach
    {
        size_t index = 0;
        unsigned state = 0; // 0 empty, 1 is full
        unsigned obstacle = 0;
        ofVec3f position = ofVec3f(0,0,0);
        Voxel(){};
        Voxel(size_t index, const ofVec3f &position)
        {
            //When parameters shadow the class members, the this-> removes the ambiguity
            this->index = index;
            this->position = position;
        }
        Voxel(const Voxel& other)
        {
            index = other.index;
            position = other.position;
            state = other.state; // Passing this in the copy constructor, otherwise the vector<> won't copy them
            obstacle = other.obstacle;
        }
        ~Voxel()
        {
            
        }
    };
    
    void          setVoxelAsObstacle(int i, unsigned type); //The voxel as an obstacle is Hard-coded for testing porpuses

    std::vector<Voxel> voxels;
    size_t  m_nx, m_ny, m_nz; //number of vertices
    size_t  m_nCols, m_nRows, m_nLayers; // Columns X, Rows Y, and Layers Z
    size_t  width, height, depth = 1; // Columns X, Rows Y, and Layers Z
    float   m_voxelSize, m_dx, m_dy, m_dz; // voxel size
    float   m_normalizeSizeFactor;
};
