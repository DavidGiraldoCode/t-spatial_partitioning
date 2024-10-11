//
//  RayIntersectionScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-30.
//
/**
 TODO:
 Use the position of the RayOrigin in the Grid to define from where the steps of the intersection test will start. Avoinding O(w * h * d)
 Use the Ray reach to define how many steps to compute, intead of doing it by checking the "lamba t"
 Use the inidividual X Y Z components of the Ray direction to determine if the test will move forward or backward in the grid.
 Evaluate if it usueful to get the (i, j, k) 3D indices from the Grid.
 **/
#include "RayIntersectionScene.hpp"

RayIntersectionScene::RayIntersectionScene()
{
    sceneName = "Ray Intersection";
};


RayIntersectionScene::~RayIntersectionScene()
{
    
};

void RayIntersectionScene::setup()
{
    Scene::setup();
    
    // =========================================== Actors
    ray = Ray();
    rayOriginPosition = ofVec3f(0,0,0);
    rayTargetPosition = ofVec3f(gridWidth * VOXEL_SIZE / 2,
                                gridHeight * VOXEL_SIZE / 2,
                                gridDepth * VOXEL_SIZE / -2);
    ray.setDirection((rayTargetPosition-rayOriginPosition).normalize());//ofVec3f(0,0,-1)); // Forward Z (-1)
    
    //Create the meshes to visualize the ray origin, target and reach
    rayOriginMesh.set(20,8);
    rayTargetMesh.set(10,8);
    
    //The ray mesh needs to be define in local space.
    rayMesh.getMesh().addVertex(ofVec3f(-2,0,0));
    rayMesh.getMesh().addVertex(ofVec3f(0,0,ray.getReach() * -1));//ray.getDirection() * ray.getReach());
    rayMesh.getMesh().addVertex(ofVec3f(2,0,0));
    rayMesh.getMesh().setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    rayOriginMesh.setGlobalPosition(rayOriginPosition.x, rayOriginPosition.y, rayOriginPosition.z);
    rayTargetMesh.setGlobalPosition(rayTargetPosition.x, rayTargetPosition.y, rayTargetPosition.z);
    
};

void computeAxisAlignIntersection(const ofVec3f & worldNormal,
                                        UniformGrid & uniformGridRef,
                                        Ray & testRay,
                                        ofVec3f & planeNormal,
                                  const float startingIndex,
                                  const float range,
                                        float lamba,
                                  const float stepSize)
{
    //Z planess
    //Do a behind-check to avoid computing intersection when the ray is hiting the back of the surface.
    //if(zPlaneNormal.dot(ray.getDirection()) >= 0) break;
    
    //if(worldNormal.dot(testRay.getDirection()) < 0) // The ray is going in the oposite direction than the world Z normal
        //planeNormal *= 1;
    
    // If ray is going in the same direction as the world normal, the PlaneNormal needs to flip
    // to consider the voxels' faces that are in the direction [MaxBound -> 0]
    if(worldNormal.dot(testRay.getDirection()) > 0)
        planeNormal *= -1;
        
    
    // dot = 0 means that the ray is orthogonal to the world, and thus no intersection happen (or infinite)
    if(worldNormal.dot(testRay.getDirection()) != 0)
    {
        int planeIndex; // If the plane normal is negative, we traverse the planes from [depth -> 0]
        std::cout << planeNormal       << " PlaneNormal\n";
        std::cout << testRay.getDirection() << " Ray Direction\n";
        std::cout << testRay.getOrigin()    << " Ray Origin\n";
        std::cout << startingIndex      << " startingIndex\n";
        std::cout << range              << " range\n";
        
        ofVec3f planePosition;
        
        for(size_t i = 1; i <= (range - startingIndex); i++)
        {
            /**
            depthRange - index3D.z = absoluteDistance
            since depthRange - absoluteDistance = index3D.z, we use this equation to offset the plane position adding (or substrating) i
            depthRange - absoluteDistance - i = index3D.z - i
             **/
            // -1 becase the voxel grid grows away from the camera.
            
            //std::cout << planeIndex << " planeIndex\n";
            int flip; // -1 becase the grid grows away from the camera, but only for Z
            if(planeNormal.z != 0)
                flip = i == 0 ? 1 : -1; // Sneaky way to avoid having -0
            else
                flip = 1;
            
            if(planeNormal.x != 0) // Meaning, is the X axis what is being tested
            {
                planeIndex = planeNormal.x == 1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.x = planeIndex * stepSize;
            }
            if(planeNormal.y != 0) // Meaning, is the Y axis what is being tested
            {
                planeIndex = planeNormal.y == 1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.y = planeIndex * stepSize;
            }
                
            if(planeNormal.z != 0) // Meaning, is the Z axis what is being tested
            {
                planeIndex = planeNormal.z == -1 ? (range - (range - startingIndex)) - i : startingIndex + i;
                planePosition.z = planeIndex * stepSize * flip;
            }
                
            
            
            bool intersectionTest = testRay.intersectPlane(planeNormal,
                                                           planePosition,
                                                           testRay.getOrigin(),
                                                           testRay.getDirection(),
                                                           lamba);
            //stop doing intersection test because
            // 1. Lamba may be grater than the reach
            std::cout << planePosition << " PlanePosition | "
                      << intersectionTest << " intersectionTest | "
                      << testRay.getIntersectionPoint() << " Intersection Point |\n";
            
            if (!intersectionTest) break; //This avoiding jumping voxels
            
            int voxelIndex = uniformGridRef.isPointInsideAVoxelGivenRayDirection(testRay.getIntersectionPoint(),
                                                                                 planeNormal,
                                                                                 testRay.getDirection());
            
            std::cout << uniformGridRef.get3DunitIndex(testRay.getIntersectionPoint()) << " 3D index \n";
            
            uniformGridRef.setIntersection(voxelIndex);
        }
        //std::cout << '\n';
    }
}

void RayIntersectionScene::update()
{
    //upadate the ray vector
    ray.setOrigin(rayOriginPosition);
    ray.setDirection((rayTargetPosition - rayOriginPosition).normalize()); // The forward vector in this scene is -1
    
    ofVec3f xPlaneNormal = ofVec3f(1,0,0);
    ofVec3f yPlaneNormal = ofVec3f(0,1,0);
    ofVec3f zPlaneNormal = ofVec3f(0,0,1);//ray.getDirection() * -1;
    
    ofVec3f world_X_Normal = ofVec3f(1,0,0);
    ofVec3f world_Y_Normal = ofVec3f(0,1,0);
    ofVec3f world_Z_Normal = ofVec3f(0,0,1);
    
    float lambaT;
    
    // Ray testing STARTING POINT
    // This is the position inside the 3D array from where the ray traversal test will start with respect to the Voxel Grid
    // 0 based [0,0,0] -> [width - 1, height - 1, depth - 1] inclusive, meaning uniformGrid[width, height, depth] is NOT a valid position within bounds
    ofVec3f index3D = uniformGrid.get3DunitIndex(ray.getOrigin());
    
    float depthRange = index3D.z + (int)(ray.getReach()/VOXEL_SIZE); //how far along the depth it should go
    float widthRange = index3D.x + (int)(ray.getReach()/VOXEL_SIZE); //how far along the width planes it should go
    float heightRange = index3D.y + (int)(ray.getReach()/VOXEL_SIZE); //how far along the height planes it should go
    
    computeAxisAlignIntersection(world_X_Normal, uniformGrid, ray, xPlaneNormal, index3D.x, widthRange, lambaT, VOXEL_SIZE);
    computeAxisAlignIntersection(world_Y_Normal, uniformGrid, ray, yPlaneNormal, index3D.y, heightRange, lambaT, VOXEL_SIZE);
    computeAxisAlignIntersection(world_Z_Normal, uniformGrid, ray, zPlaneNormal, index3D.z, depthRange, lambaT, VOXEL_SIZE);
    
    /*X planes
    if(world_X_Normal.dot(ray.getDirection()) < 0)
        xPlaneNormal.x = 1;
    if(world_X_Normal.dot(ray.getDirection()) > 0)
        xPlaneNormal.x = -1;
    
    if(world_X_Normal.dot(ray.getDirection()) != 0)
    {
        int direction; // If the plane normal is positive, we traverse the planes from [width -> 0]
        for(size_t i = index3D.x; i < widthRange; i++)
        {
            direction = xPlaneNormal.x == 1 ? index3D.x - (widthRange - i) : i;
            ofVec3f planePosition = ofVec3f(direction * VOXEL_SIZE, 0, 0); // second plane in the Z axis away from the camera (depth)
            bool intersectionTest = ray.intersectPlane(  xPlaneNormal,
                                                         planePosition,
                                                         ray.getOrigin(),
                                                         ray.getDirection(),
                                                         lambaT);
            
            int voxelIndex = uniformGrid.isPointInsideAVoxelGivenRayDirection(ray.getIntersectionPoint(),
                                                                              ray.getDirection());
            uniformGrid.setIntersection(voxelIndex);
        }
    }
    
    //Y planes
    if(world_Y_Normal.dot(ray.getDirection()) < 0)
        yPlaneNormal.y = 1;
    if(world_Y_Normal.dot(ray.getDirection()) > 0)
        yPlaneNormal.y = -1;
    
    if(world_Y_Normal.dot(ray.getDirection()) != 0)
    {
        int direction; // If the plane normal is positive, we traverse the planes from [height -> 0]
        for(size_t i = index3D.y; i < heightRange; i++)
        {
            direction = yPlaneNormal.y == 1 ? index3D.y - (heightRange - i) : i;
            ofVec3f planePosition = ofVec3f(0, direction * VOXEL_SIZE, 0); // second plane in the Z axis away from the camera (depth)
            bool intersectionTest = ray.intersectPlane(  yPlaneNormal,
                                                         planePosition,
                                                         ray.getOrigin(),
                                                         ray.getDirection(),
                                                         lambaT);
            
            int voxelIndex = uniformGrid.isPointInsideAVoxelGivenRayDirection(ray.getIntersectionPoint(),
                                                                              ray.getDirection());
            uniformGrid.setIntersection(voxelIndex);
        }
    }
     */
    
    
    //Abstraction
    
    
    
    /*/Z planess
    //Do a behind-check to avoid computing intersection when the ray is hiting the back of the surface.
    //if(zPlaneNormal.dot(ray.getDirection()) >= 0) break;
    
    if(world_Z_Normal.dot(ray.getDirection()) < 0) // The ray is going in the oposite direction than the world Z normal
        zPlaneNormal.z = 1;
    
    // The ray is going in the same direction as the world Z normal, the PlaneNormal needs to flip
    // to consider the voxels' faces that are in the direction [depth -> 0]
    if(world_Z_Normal.dot(ray.getDirection()) > 0)
        zPlaneNormal.z = -1;
    
    // dot = 0 means that the ray is orthogonal to the Z normal, and thus no intersection (or infinite)
    if(world_Z_Normal.dot(ray.getDirection()) != 0) 
    {
        int planeIndex; // If the plane normal is negative, we traverse the planes from [depth -> 0]
//        std::cout << zPlaneNormal       << " zPlaneNormal\n";
//        std::cout << ray.getDirection() << " Ray Direction\n";
//        std::cout << ray.getOrigin()    << " Ray Origin\n";
//        std::cout << index3D.z          << " index3D.z\n";
//        std::cout << depthRange         << " depthRange\n";
        
        for(size_t i = 1; i <= (depthRange - index3D.z); i++)
        {
        
//            depthRange - index3D.z = absoluteDistance
//            since depthRange - absoluteDistance = index3D.z, we use this equation to offset the plane position adding i
//            depthRange - absoluteDistance - i = index3D.z - i
            
            planeIndex = zPlaneNormal.z == -1 ? (depthRange - (depthRange - index3D.z)) - i : index3D.z + i;// - (depthRange - i) : i;
            // -1 becase the voxel grid grows away from the camera.
            //std::cout << planeIndex << " planeIndex\n";
            
            int flip = i == 0 ? 1 : -1; // Sneaky way to avoid having -0
            ofVec3f zPlanePosition = ofVec3f(0, 0, planeIndex * VOXEL_SIZE * flip); // -1 becase the grid grows away from the camera
            bool intersectionTest = ray.intersectPlane(  zPlaneNormal,
                                                         zPlanePosition,
                                                         ray.getOrigin(),
                                                         ray.getDirection(),
                                                         lambaT);
            //stop doing intersection test because
            // 1. Lamba may be grater than the reach
//            std::cout << zPlanePosition << " zPlanePosition | "
//                      << intersectionTest << " intersectionTest | "
//                      << ray.getIntersectionPoint() << " Intersection Point |"
//                      << uniformGrid.get3DunitIndex(ray.getIntersectionPoint()) << " 3D index \n";
            
            if (!intersectionTest) break;
            
            int voxelIndex = uniformGrid.isPointInsideAVoxelGivenRayDirection(ray.getIntersectionPoint(),
                                                                              ray.getDirection());
            
            uniformGrid.setIntersection(voxelIndex);
        }
        //std::cout << '\n';
    }
     */
    
    
    /*
     std::cout << "intersectionTest: " << intersectionTest
             << "\n | Ray Origin Position: " << rayOriginPosition
             << "\n | Ray ["<< i <<"] Interwsection Point: " << ray.getIntersectionPoint()
             << "\n | Intersection ["<< i <<"] Point Index in Grid: " << voxelIndex
             << "\n | Ray Origin Position in Grid: " << uniformGrid.isPointInsideAVoxel(rayOriginPosition)
             <<'\n';
     */
    
    //Update visulizer
    rayOriginMesh.setGlobalPosition(rayOriginPosition.x, rayOriginPosition.y, rayOriginPosition.z);
    rayTargetMesh.setGlobalPosition(rayTargetPosition.x, rayTargetPosition.y, rayTargetPosition.z);
    rayMesh.setPosition(rayOriginPosition);
    
    rayMesh.lookAt(rayTargetPosition);
    
    //TODO
    /**
     Visualize the voxels being intersertec by the ray
        Create the method for moving forward on the grid by units [i,j,k]
        Parametrize the Ray so it can be attached to the boid and compute the intersection.
     **/
};

void RayIntersectionScene::draw()
{
    ofBackground(255,255,255,255); // draw a gradient in the background with ofBackgroundGradient(ofColor(10), ofColor(50));
    
    ofEnableDepthTest();
    cam.begin();
        
        roadMaterial.begin();
        environmentGround.draw();
        roadMaterial.end();
        
        environmentGround.drawAxes(500);
        ofSetColor(100, 100, 100);
        obstaclesBoundingVolume.drawWireframe();
        
        rayOriginMesh.draw(); // <------------------------------- 3D cursor draw call
        
        ofSetColor(255, 100, 100);
        rayTargetMesh.draw();
        rayMesh.drawWireframe(); //the dir vector of the bois an also the Ray

    //
    //--------   Uniform grid
    //
        
        for(size_t i = 0; i < uniformGrid.getGridSize(); i++)
        {
            ofVec3f pos = uniformGrid.getVoxelPositionByIndex(i);
            
            voxelMesh.setGlobalPosition(pos.x + (VOXEL_SIZE/2), pos.y + (VOXEL_SIZE/2), pos.z - (VOXEL_SIZE/2));
            
            if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 0) // The voxel is an obstacle
            {
                ofSetColor(0, 0, 255, 80);
                voxelMesh.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 1 && uniformGrid.getVoxelState(i) == 1) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                voxelMesh.drawFaces();
            }
            else if(uniformGrid.getVoxelObstacle(i) == 0 && uniformGrid.getVoxelState(i) == 1)//Boid flys inside
            {
//                ofSetColor(0, 255, 0, 5);
//                voxelMesh.drawFaces();
            }
            //voxelMesh.drawWireframe();
            
            // VISUALIZING INTERSECTIONS
            
            if(uniformGrid.getVoxelIntersectionState(i) == true) //Boid flys inside of an obstacle
            {
                ofSetColor(255, 0, 0, 50);
                voxelMesh.drawFaces();
            }
        }
    uniformGrid.clearIntersections();
    
    ofDisableDepthTest();
    cam.end();
    
    //
    // GUI
    //
    guiFramesPerSecond.set(ofGetFrameRate());
    gui.draw();
};

void RayIntersectionScene::keyPressed(int key)
{

    switch (key) {
        case KeyCode::W:
            //std::cout << "Front \n";
            rayOriginPosition.z -= CURSOR_SPEED;
            break;
        case KeyCode::S:
            //std::cout << "Back \n";
            rayOriginPosition.z += CURSOR_SPEED;
            break;
        case KeyCode::A:
            rayOriginPosition.x -= CURSOR_SPEED;
            //std::cout << "Left \n";
            break;
        case KeyCode::D:
            rayOriginPosition.x += CURSOR_SPEED;
            //std::cout << "Right \n";
            break;
        case KeyCode::Q: // DOWN
            rayOriginPosition.y -= CURSOR_SPEED;
            break;
        case KeyCode::E: // UP
            rayOriginPosition.y += CURSOR_SPEED;
            break;
        case KeyCode::SPACE:
            //std::cout << "Space \n";
            break;
        case KeyCode::UP:
            rayTargetPosition.y += CURSOR_SPEED;
            //std::cout << "Up \n";
            break;
        case KeyCode::DOWN:
            rayTargetPosition.y -= CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        case KeyCode::RIGHT:
            rayTargetPosition.x -= CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        case KeyCode::LEFT:
            rayTargetPosition.x += CURSOR_SPEED;
            //std::cout << "Down \n";
            break;
        default:
            break;
    }
    
    //Updating position of ray in Voxel Grid
    //std::cout << "\n rayOriginPosition: "<<rayOriginPosition << '\n';
    //std::cout << "ray normal: "<<ray.getDirection().getNormalized() << '\n';
    //std::cout << "ray 3D position in Grid: "<< uniformGrid.get3DunitIndex(rayOriginPosition) << '\n';
    
    int cursorNewPos = uniformGrid.isPointInsideAVoxel(rayOriginPosition);
    
    //std::cout << "Cursor Position in Grid: " << cursorNewPos<< '\n';
    //TEMPORAL using Boid's updatePositionInWorldGrid
    
    if(cursorNewPos == cursorCurrentPos)
    {
        cursorPreviousPos = cursorCurrentPos;
        return;
    }; //We have not moved to another voxel, do nothing
    
    //We have indeed change to another place
    cursorCurrentPos = cursorNewPos;
    
    if(cursorCurrentPos != -1) // We are still inside the grid, so notify the new voxel
        uniformGrid.addObjectToVoxel(cursorCurrentPos);
    
    
    if(cursorPreviousPos != -1) //The boid was not outside, notify previous voxel
        uniformGrid.removeObjectFromVoxel(cursorPreviousPos);
    
     //Update position.
    cursorPreviousPos = cursorCurrentPos;
}
