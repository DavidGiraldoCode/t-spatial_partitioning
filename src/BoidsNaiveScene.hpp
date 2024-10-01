//
//  BoidsNaiveScene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-01.
//
#include "Scene.hpp"
//#include "Boid.hpp"
#include "BoidsManager.hpp"

class BoidsNaiveScene : public Scene
{
public:
    BoidsNaiveScene();
    ~BoidsNaiveScene();
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    
    //==================================== Actors
    BoidsManager                    boidsManager;
    //std::vector<Boid>               boids = {};
    std::vector<ofSpherePrimitive>  boidMeshes = {};
};
