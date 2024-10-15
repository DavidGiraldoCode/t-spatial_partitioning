//
//  SensingBoidsScene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-10-14.
//
#pragma once
#include "Scene.hpp"
#include "Drone.hpp"

class SensingBoidsScene : public Scene
{
public:
    SensingBoidsScene(){};
    SensingBoidsScene(const std::string & name);
    ~SensingBoidsScene() = default;
    
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;
    
    //================================= Actors
    
    //BoidsManager                    boidsManager;
    //std::vector<Drone>              drones = {};
};
