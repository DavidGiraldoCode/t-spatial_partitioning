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
    UniformGrid(size_t nx, size_t ny, size_t nz, ofVec3f minPoint, ofVec3f maxPoint);
    ~UniformGrid();
    void getVoxelByWorldCoordinates(ofVec3f point);
    void getVoxelByIndex(size_t index);
    const size_t getGridSize();
private:
    struct Voxel
    {
        size_t m_index = 0;
        ofVec3f m_position = ofVec3f(0,0,0);
        Voxel(size_t index, ofVec3f position)
        {
            m_index = index;
            m_position = position;
        }
        Voxel(const Voxel& other)
        {
            m_index = other.m_index;
            m_position = other.m_position;
        }
        ~Voxel();
    };
    std::vector<Voxel> voxels;
    size_t m_nx, m_ny, m_nz; //number of vertices
    size_t m_nCols, m_nRows, m_nLayers; // Columns X, Rows Y, and Layers Z
    float m_dx, m_dy, m_dz; // voxel size
};
