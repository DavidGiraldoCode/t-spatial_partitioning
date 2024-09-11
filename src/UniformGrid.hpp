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
    UniformGrid(size_t width, size_t height, size_t depth, ofVec3f pivot);
    ~UniformGrid();
    void            getVoxelByWorldCoordinates(ofVec3f point);
    void            getVoxelByIndex(size_t index);
    ofVec3f         getVoxelPositionByIndex(size_t index);
    const size_t    getGridSize();
private:
    struct Voxel
    {
        size_t index = 0;
        unsigned state = 0; // 0 empty, 1 is full
        ofVec3f position = ofVec3f(0,0,0);
        Voxel(){};
        Voxel(size_t index, ofVec3f position)
        {
            //When parameters shadow the class members, the this-> removes the ambiguity
            this->index = index;
            this->position = position;
        }
        Voxel(const Voxel& other)
        {
            index = other.index;
            position = other.position;
        }
        ~Voxel()
        {
            
        }
    };
    std::vector<Voxel> voxels;
    size_t  m_nx, m_ny, m_nz = 2; //number of vertices
    size_t  m_nCols, m_nRows, m_nLayers = 1; // Columns X, Rows Y, and Layers Z
    size_t  width, height, depth = 1; // Columns X, Rows Y, and Layers Z
    float   m_voxelSize = 10, m_dx, m_dy, m_dz; // voxel size
};
