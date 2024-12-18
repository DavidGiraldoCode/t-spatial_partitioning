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

// ================= 🚧 The current grid

UniformGrid::UniformGrid(size_t width, size_t height, size_t depth, float VOXEL_SIZE)
{
    std::cout << "Building the grid with voxel origin at corner [0,0,0]" << '\n';
    std::cout << width << height << depth << '\n';
    
    unsigned voxelCount = width * height * depth;
    std::cout << "voxelCount: " << voxelCount << '\n';
    
    m_VOXEL_SIZE = VOXEL_SIZE;
    
    m_voxelSize = (float)VOXEL_SIZE * 1.0f; // A brute force casting to be sure
    m_normalizeSizeFactor = (float)(1.0f / m_voxelSize);
    
    m_nx = width <= 0 ? 2 : width + 1;
    m_ny = height <= 0 ? 2 : height + 1;
    m_nz = depth <= 0 ? 2 : depth + 1;
    
    m_nCols = width;
    m_nRows = height;
    m_nLayers = depth; //Layer as in depth of layers
    
    unsigned verticesCount = m_nx * m_ny * m_nz;
    
    for(size_t i = 0; i < voxelCount; i++)
    {
        //These coordinates disregard the size of the voxel
        float x = i % width;
        float y = (i / width) % height;
        float z = i  / (width * height);
        
        //std::cout << 'x' << x << 'y' << y << 'z' << z << '\n';
        
        //These coordnate consider the size of the voxel //TODO and soon the offset position on the grid in world space
        float worldX = (x * m_voxelSize); //offset of the min
        float worldY = (y * m_voxelSize); //offset of the min
        
        z = z != 0 ? (z * -1) : 0; // Right-handed coordinate system, this avoid having -0, when z = 0, then z * -1 = -0
        float worldZ = (z * m_voxelSize);
        
        //std::cout << "worldX: " << worldX << " worldY: " << worldY << " worldZ: " << worldZ << '\n';
        
        Voxel v = Voxel(i, ofVec3f(worldX, worldY, worldZ));
        voxels.push_back(v);
        
        // RANDOM assignation of the Voxel as obstacle
        float randomObstacleState = ofRandom(0, 1);
        //std::cout << "randomObstacleState: " << randomObstacleState << '\n';
        float OBSTACLES_POBALITIY = 0.95; // Gives more chances of voxels being emty spaces
        bool isEmpty = (randomObstacleState > OBSTACLES_POBALITIY);
        if(worldX >= 400 && worldX < 1400 &&
           worldY >= 400 && worldY < 1400)
            setVoxelAsObstacle(i, isEmpty);
        
        //if(y == 0) // Shading the ground as obstacles
            //setVoxelAsObstacle(i, true);
        
        if(isEmpty)// if it an obstacle, save the index, TODO, I need to change the readability of the logic
            obstaclesIndexs.push_back(i);
        
        // ===============================================================================================================
        // For testing purposes, I am hard-coding obstacles on the grid  🚧
        // ===============================================================================================================
        
        //Single obstacle
        /*
        if(worldX >= 900 && worldX < 1000 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        */
        /* in-line obstacles */
        /*
        if(worldX >= 900 && worldX < 1000 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -100)
            setVoxelAsObstacle(i, true);
        
        if(worldX >= 900 && worldX < 1000 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -800)
            setVoxelAsObstacle(i, true);
        
        if(worldX >= 900 && worldX < 1000 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX >= 900 && worldX < 1000 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -2400)
            setVoxelAsObstacle(i, true);
        */
        /* in-line obstacles */
        /*
        int lineOne = 600;
        int lineTwo = 900;
        int lineThree = 1200;
        
        //------------------ lineOne
        if(worldX == lineOne &&
           worldY == 900 &&
           worldZ == -100)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineOne &&
           worldY == 900 &&
           worldZ == -800)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineOne &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineOne &&
           worldY == 900 &&
           worldZ == -2400)
            setVoxelAsObstacle(i, true);
        //-------------------- lineTwo
        if(worldX == lineTwo &&
           worldY == 900 &&
           worldZ == -100)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineTwo &&
           worldY == 900 &&
           worldZ == -800)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineTwo &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineTwo &&
           worldY == 900 &&
           worldZ == -2400)
            setVoxelAsObstacle(i, true);
        
        //-------------------- lineThree
        if(worldX == lineThree &&
           worldY == 900 &&
           worldZ == -100)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineThree &&
           worldY == 900 &&
           worldZ == -800)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineThree &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == lineThree &&
           worldY == 900 &&
           worldZ == -2400)
            setVoxelAsObstacle(i, true);
        */
        /* wall obstacle */
        /*
        if(worldX >= 600 && worldX < 1200 &&
           worldY >= 900 && worldY < 1000 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        */
        
        /* zig-zag */
        /*
        if(worldX == 900 &&
           worldY == 900 &&
           worldZ == -400)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 600 &&
           worldY == 900 &&
           worldZ == -800)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 1100 &&
           worldY == 900 &&
           worldZ == -1200)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 600 &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 1100 &&
           worldY == 900 &&
           worldZ == -2000)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 600 &&
           worldY == 900 &&
           worldZ == -2400)
            setVoxelAsObstacle(i, true);
        
        */
        // in-line horizontal
        /*
        if(worldX == 700 &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 900 &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        
        if(worldX == 1100 &&
           worldY == 900 &&
           worldZ == -1600)
            setVoxelAsObstacle(i, true);
        */
//        if(worldX == 1800 &&
//           worldY >= 800 && worldY < 1200 &&
//           worldZ <= -800 && worldZ > -2000)
//            setVoxelAsObstacle(i, true);
        
        //std::cout << "voxels["<<i<<"].position = " << voxels[i].position << '\n';
    }
    std::cout << "voxels.size(): " << voxels.size() << '\n';
    std::cout << "obstaclesIndexs.size(): " << obstaclesIndexs.size() << '\n';
}


           
UniformGrid::~UniformGrid()
{
    //std::cout << "Bye bye UniformGrid" << '\n';
}

//Public

const  ofVec3f UniformGrid::get3DunitIndex(const ofVec3f &point)
{
    //std::cout << point << " point \n";
    float pX = floor(point.x * m_normalizeSizeFactor); // m_normalizeSizeFactor = 1/m_voxelSize;
    float pY = floor(point.y * m_normalizeSizeFactor);
    
    //Multiplying *-1 will create an artefact, a jumping voxel
    float pZ = floor(point.z * m_normalizeSizeFactor);// * -1; //Recall that we have defined the deepth of the grid to be far away from the camera
    
    
    //std::cout << "Test for floor: " << (point.z) * m_normalizeSizeFactor << '\n';
    //float z = (point.z) * m_normalizeSizeFactor * -1;
    //std::cout << "Test for floor: " << floor(z) << '\n';
    //std::cout << pX << " pX |" << pY << " pY |" << pZ << " pX |\n";
    //std::cout << point.z << " point.z |\n";
    
    pZ = point.z == 0 ? pZ : pZ * -1.0f ; // A brute force to avoid C++ flooring 5.0 to 4 for some reason
    
    
    //std::cout << pX << " pX |" << pY << " pY |" << pZ << " pZ |\n";
    
    bool inColsBounds   = pX >= 0 && pX < m_nCols;
    bool inRowsBounds   = pY >= 0 && pY < m_nRows;
    bool inLayersBounds = pZ >= 0 && pZ < m_nLayers;
    
    if(!inColsBounds || !inRowsBounds || !inLayersBounds)
    {
        //TODO
        /**
         A more comprenhensive solution, this is giving information of the last position from where the boid exited the grid
         **/
        pX = pX < 0 ? -1 : pX >= m_nCols   ? m_nCols   : pX ;
        pY = pY < 0 ? -1 : pY >= m_nRows   ? m_nRows   : pY ;
        pZ = pZ < 0 ? -1 : pZ >= m_nLayers ? m_nLayers : pZ ;
        
        if (pZ == -0.0f)
        {
            //std::cout << pZ << " -> -0\n";
            pZ = 0.0f;
        }
        
        return {pX, pY, pZ}; //previously {-1, -1, -1};
    }
        

    int indexInOneD = pZ * m_nCols * m_nRows + pY * m_nCols + pX;
    
    if(indexInOneD < 0 || indexInOneD >= voxels.size())
        return {-1, -1, -1};
    
    //std::cout << "Point is at voxel["<< indexInOneD <<"] : "<<voxels[indexInOneD].position << '\n';
    return {pX, pY, pZ};
}

const int UniformGrid::isPointInsideAVoxel(const ofVec3f &pointQuery) const
{
    //std::cout << "pointQuery ["<< pointQuery <<"]"<< '\n';
    //std::cout << m_normalizeSizeFactor << "  m_normalizeSizeFactor \n";
    //Casting values and de-scaling the world position to units and increments of 1
    int pX = floor(pointQuery.x * m_normalizeSizeFactor); // m_normalizeSizeFactor = 1/m_voxelSize;
    int pY = floor(pointQuery.y * m_normalizeSizeFactor);
    
    //The -1 is an error in the math
    int pZ = floor((pointQuery.z * -1) * m_normalizeSizeFactor);// * -1; //Recall that we have defined the deepth of the grid to be far away from the camera
    
    //std::cout << "unit positions["<< pX <<' '<< pY << ' ' << pZ <<"]"<< '\n';
    
    bool inColsBounds = pX >= 0 && pX < m_nCols;
    bool inRowsBounds = pY >= 0 && pY < m_nRows;
    bool inLayersBounds = pZ >= 0 && pZ < m_nLayers;
    
    if(!inColsBounds || !inRowsBounds || !inLayersBounds)
        return -1;

    int indexInOneD = pZ * m_nCols * m_nRows + pY * m_nCols + pX;
    
    if(indexInOneD < 0 || indexInOneD >= voxels.size())
        return -1;
    
    //std::cout << "Point is at voxel["<< indexInOneD <<"] : "<<voxels[indexInOneD].position << '\n';
    return indexInOneD;
}

const  int UniformGrid::isPointInsideAVoxelGivenRayDirection(const ofVec3f &pointQuery, const ofVec3f & planeNormal ,const ofVec3f &rayDirection) const
{
    //std::cout << "pointQuery ["<< pointQuery <<"]"<< '\n';
    //std::cout << m_normalizeSizeFactor << "  m_normalizeSizeFactor \n";
    //Casting values and de-scaling the world position to units and increments of 1
    float pX = floor(pointQuery.x * m_normalizeSizeFactor); // m_normalizeSizeFactor = 1/m_voxelSize;
    float pY = floor(pointQuery.y * m_normalizeSizeFactor);
    
    //The -1 is an error in the math
    float pZ = floor((pointQuery.z * -1) * m_normalizeSizeFactor);// * -1; //Recall that we have defined the deepth of the grid to be far away from the camera
    
    //pZ = pointQuery.z < 0 ? pZ * -1.0f : pZ;
    
    //std::cout << "unit positions["<< pX <<' '<< pY << ' ' << pZ <<"]"<< '\n';
    //std::cout << rayDirection << " ray direction\n";
    /*Checking directions*/
    //if (rayDirection.x < 0) // if the Ray is pointing in the same direction as the world X Normal
    //    pX -= 1; // The Voxel is hitting is not from [0 -> width] but [width -> 0]
    if (planeNormal.x != 0)
    {
        if (rayDirection.x < 0) // if the Ray is pointing in the oposite direction as the world Y Normal
            pX -= 1; // The Voxel is hitting is not from [0 -> height] but [height -> 0]
    }
    
    if (planeNormal.y != 0)
    {
        if (rayDirection.y < 0) // if the Ray is pointing in the oposite direction as the world Y Normal
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
    
    //std::cout << "Point is at voxel["<< indexInOneD <<"] : "<<voxels[indexInOneD].position << '\n';
    return indexInOneD;
}

void UniformGrid::getVoxelByWorldCoordinates(const ofVec3f & point)
{
    
}

void UniformGrid::getVoxelByIndex(size_t index)
{
    
}

const ofVec3f UniformGrid::getVoxelWorldCenterPosition(int voxelIndex) const
{
    ofVec3f positionInWorldSpace = getVoxelPositionByIndex(voxelIndex);
    //std::cout << positionInWorldSpace << " position In GridSpace\n";
    float offSetToCenter = m_VOXEL_SIZE * 0.5f;
//    
//    positionInWorldSpace.x *= (m_VOXEL_SIZE);
//    positionInWorldSpace.y *= (m_VOXEL_SIZE);
//    positionInWorldSpace.z *= (m_VOXEL_SIZE);
    
    positionInWorldSpace.x += offSetToCenter;
    positionInWorldSpace.y += offSetToCenter;
    positionInWorldSpace.z += (offSetToCenter * -1);
    
    
    return positionInWorldSpace;
}

const ofVec3f UniformGrid::getVoxelPositionByIndex(size_t index) const
{
    return voxels[index].position;
}

const ofVec3f& UniformGrid::getObstaclePositionByIndex(size_t index) const
{
    //TODO needs invariance, otherwise the index could be out of bounce
    return voxels[obstaclesIndexs[index]].position;
}

const  bool UniformGrid::isVoxelAnObstacle(int i) const
{
    if(i < 0 || i > voxels.size()) return false;
    
    return voxels[i].obstacle == VoxelType::OBSTACLE;
}

const size_t UniformGrid::getGridSize()
{
    return voxels.size();
}

void UniformGrid::removeObjectFromVoxel(int i)
{
    if(i < 0 || i >= voxels.size()) return;
    
    voxels[i].state = 0;
    //std::cout << "Removing from voxel " << i << '\n';
}

void UniformGrid::addObjectToVoxel(int i)
{
    if(i < 0 || i >= voxels.size()) return;
    
    voxels[i].state = 1;
    //std::cout << "Adding to voxel " << i << '\n';
}

const  int UniformGrid::getVoxelState(int i) const
{
    return voxels[i].state;
}

const  int UniformGrid::getVoxelObstacle(int i) const
{
    return voxels[i].obstacle;
}

//
void UniformGrid::clearIntersections()
{
    for(size_t i = 0; i < voxels.size(); i++)
    {
        voxels[i].intersected = false;
    }
}

void UniformGrid::setIntersection(int i)
{
    if(i < 0 || i >= voxels.size()) return;
    
    voxels[i].intersected = true;
}

const bool UniformGrid::getVoxelIntersectionState(int i) const
{
    return voxels[i].intersected;
}
// PRIVATE

void UniformGrid::setVoxelAsObstacle(int i, unsigned type)
{
    voxels[i].obstacle = type;
}
