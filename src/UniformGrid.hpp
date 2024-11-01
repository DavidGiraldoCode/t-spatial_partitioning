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
    
    float m_VOXEL_SIZE = 0;
    
    UniformGrid(){};
    UniformGrid(size_t nx, size_t ny, size_t nz, ofVec3f minPoint, ofVec3f maxPoint);
    UniformGrid(size_t width, size_t height, size_t depth, ofVec3f pivot, float VOXEL_SIZE);
    /**
     * Constructor of a uniform grid with cell origin on the bottom left front [0,0,0] corner
     * @param width Number of voxels in the x axis
     * @param height Number of voxels in the y axis
     * @param depth Number of voxels in the z axis
     * @param VOXEL_SIZE Size of the voxel, can be thought as the resolution of the obstacles
     */
    UniformGrid(size_t width, size_t height, size_t depth, float VOXEL_SIZE);
    ~UniformGrid();
           void          getVoxelByWorldCoordinates(const ofVec3f &point);
    // TODO add a method that allow for unit increment (i,j,k)
           void          getVoxelByIndex(size_t index);
    
    /**
     * Gives the position of the voxel in world space
     */
    const  ofVec3f       getVoxelPositionByIndex(size_t index) const;
    
    const  ofVec3f&      getObstaclePositionByIndex(size_t index) const;
    const  size_t        getGridSize();
    const  int           isPointInsideAVoxel(const ofVec3f &pointQuery) const;
    
    /**
     * Checks if the intersection point of the ray is inside a voxel in the grid.
     * This takes into consideration the orientation of the ray to compare it with the normal of the voxel agaist.
     * @param pointQuery The intersection point
     * @param planeNormal The plane normal representing the orientation of the voxel
     * @param rayDirection The direction of the ray
     * @return A 1D index of the voxel that was intersected, or -1 if any voxel was intersected
     * @note Compleity O(1)
     */
    const  int           isPointInsideAVoxelGivenRayDirection(const ofVec3f &pointQuery,
                                                              const ofVec3f & planeNormal,
                                                              const ofVec3f &rayDirection) const;
           void          removeObjectFromVoxel(int i);
           void          addObjectToVoxel(int i);
    const  int           getVoxelState(int i) const;
    const  int           getVoxelObstacle(int i) const; //TODO this should be state instead
    const  ofVec3f       get3DunitIndex(const ofVec3f &point);
    //For Debugging
           void          clearIntersections();
    
    /**
     * Flags the voxels as being intersected, shading it.
     * @note This is for debugging purposes
     */
           void          setIntersection(int i);
    
    /**
     * Checks if a voxel is an obstacle by a given index
     * @param i The index in 1D
     * @return `true` if the voxel is an obstacle
     */
    const  bool          isVoxelAnObstacle(int i) const;
    
    const  bool          getVoxelIntersectionState(int i) const;
    //NEW for obstacle avoidance
    std::vector<int> obstaclesIndexs;
    
    /**
     * Given a 1D index of a voxel, returns the position in world space of the center of the voxel.
     * This is use to give the boid a way to determine if the voxel obstacle is to the right or to the left
     * @param voxelIndex The voxel, usually the one detected by the ray
     * @return A position in world space
     */
    const  ofVec3f      getVoxelWorldCenterPosition(int voxelIndex) const;
    
private:
    struct Voxel // Bucket in Rynolds PS3 approach
    {
        size_t index = 0;
        unsigned state = 0; // 0 empty, 1 is full
        /**
         * Defines this voxel as an obstacle to avoid, `0` is void, `1` is obstacle
         */
        unsigned obstacle = 0;
        ofVec3f position = ofVec3f(0,0,0);
        bool intersected = false;
        // ADD the Normals of each face, 6 normals
        /**
         [1,0,0]
         [0,1,0]
         [0,0,1]
         [-1,0,0]
         [0,-1,0]
         [0,0,-1]
         **/
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
            intersected = other.intersected;
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
    
    //New for obstacle avoidance
    /**
     * Defines the two types of voxels. Use this to make safe comparissons
     * Recall that :: is used to access values in a scope, the . operator is used for accessing members of an object (like struct members).
     */
    enum VoxelType
    {
        OBSTACLE = true,
        EMPTY = false
    };
};
