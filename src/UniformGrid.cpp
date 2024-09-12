//
//  UniformGrid.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-04.
//

#include "UniformGrid.hpp"
#include "ofVec3f.h"
#include "ofMatrix4x4.h"

UniformGrid::UniformGrid(size_t nx, size_t ny, size_t nz, ofVec3f minPoint, ofVec3f maxPoint)
{
    m_nx = nx <= 1 ? 2 : nx;
    m_ny = ny <= 1 ? 2 : ny;
    m_nz = nz <= 1 ? 2 : nz; //It will always ensures that there are at least 2 vertices on each levels
    
    m_nCols = m_nx - 1; //number of rows cells
    m_nRows = m_ny - 1; //number of columns cells
    m_nLayers = m_nz - 1; //number of layers cells
    
    m_dx = (maxPoint.x - minPoint.x) / (float)m_nCols; // Cell's width
    m_dy = m_ny > 1 ? (maxPoint.y - minPoint.y) / (float)m_nRows : 0; // Cell's height
    m_dz = (maxPoint.z - minPoint.z) / (float)m_nLayers; // layer's hight
    
    for(size_t i = 0; i < (m_nx * m_ny * m_nz); i++)
    {
        voxels.push_back(Voxel(i, ofVec3f(0,0,0)));
    }
}
UniformGrid::UniformGrid(size_t width, size_t height, size_t depth, ofVec3f pivot, float VOXEL_SIZE)
{
    std::cout << "Building the grid with pivot" << '\n';
    std::cout << width << height << depth << '\n';
    m_nx = width <= 0 ? 2 : width + 1;
    m_ny = height <= 0 ? 2 : height + 1;
    m_nz = depth <= 0 ? 2 : depth + 1;
    
    m_voxelSize = VOXEL_SIZE;
    
    unsigned voxelCount = width * height * depth;
    unsigned verticesCount = m_nx * m_ny * m_nz;
    std::cout << "voxelCount: " << voxelCount << '\n';
    
    float halfSize = m_voxelSize / 2;
    
    float boundingWidth = halfSize * width;
    float boundingHeight = halfSize * height;
    float boundingDepth = halfSize * depth;
    
    float xOffset = boundingWidth / 2 * -1;
    float yOffset = boundingHeight / 2 ;
    float zOffset = boundingDepth / 2;
//    float xOffset = (((float)width / 2) * (m_voxelSize/width)) * -1;
//    float yOffset = (((float)height / 2) * (m_voxelSize/height)) * -1;
//    float zOffset = (((float)depth / 2) * (m_voxelSize/depth));
    
    ofVec3f offsetToCenter = ofVec3f( xOffset, yOffset, zOffset);
    
    ofMatrix4x4 translateToCenterM = ofMatrix4x4();
    std::cout << "Identity Matrix:"<< '\n' << translateToCenterM << '\n';
    translateToCenterM.makeTranslationMatrix(offsetToCenter);
    std::cout << "translateToCenterM:"<< '\n' << translateToCenterM << '\n';
    //setTranslation
    //ofMatrix4x4().newTranslationMatrix(offsetToCenter);
    //translateToCenterM.makeTranslationMatrix(offsetToCenter);
    
    for(size_t i = 0; i < voxelCount; i++)
    {
        //Units
//        float x = i % m_nx; //(i % m_nx + pivot.x) + (i * width);
//        float y = (i / m_nx) % m_ny;//((i / m_ny) % m_ny) + pivot.y + (i * height);
//        float z = i  / (m_nx * m_ny);// (i / m_nx * m_ny) + pivot.z + (i * depth);
        float x = i % width; //(i % m_nx + pivot.x) + (i * width);
        float y = (i / width) % height;//((i / m_ny) % m_ny) + pivot.y + (i * height);
        float z = i  / (width * height);// (i / m_nx * m_ny) + pivot.z + (i * depth);
        
        std::cout << 'x' << x << 'y' << y << 'z' << z << '\n';
        
        float worldX = (x * m_voxelSize); //offset of the min
        float worldY = (y * m_voxelSize); //offset of the min
        float worldZ = (z * m_voxelSize)* -1; //offset of the min
        
        ofVec3f transformedToCenterPosition = ofVec3f(worldX, worldY, worldZ) * translateToCenterM;
        
        std::cout << "worldX: " << worldX << " worldY: " << worldY << " worldZ: " << worldZ << '\n';
        
        Voxel v = Voxel(i, transformedToCenterPosition);
        voxels.push_back(v);
        std::cout << "voxels["<<i<<"].position = " << voxels[i].position << '\n';
    }
    std::cout << "voxels.size(): " << voxels.size() << '\n';
}
UniformGrid::~UniformGrid()
{
    //std::cout << "Bye bye UniformGrid" << '\n';
}

void UniformGrid::getVoxelByWorldCoordinates(ofVec3f point)
{
    
}

void UniformGrid::getVoxelByIndex(size_t index)
{
    
}

ofVec3f UniformGrid::getVoxelPositionByIndex(size_t index)
{
    return voxels[index].position;
}

const size_t UniformGrid::getGridSize()
{
    return voxels.size();
}