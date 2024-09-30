//
//  RayIntersectionScene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-30.
//
//  Scene to debug the intersection of Rays using manual controller
#include "Scene.hpp"
#include "Ray.hpp"

class RayIntersectionScene: public Scene
{
public:
    RayIntersectionScene();
    ~RayIntersectionScene();
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    
    //==================================== Actors
    //Sphere representing a 3D point moved by WASD and UP DOWN to query the space
    ofSpherePrimitive               rayOriginMesh;
    ofSpherePrimitive               rayTargetMesh;
    ofVec3f                         rayOriginPosition;
    ofVec3f                         rayTargetPosition;
    of3dPrimitive                   rayMesh;
    Ray                             ray;
};
