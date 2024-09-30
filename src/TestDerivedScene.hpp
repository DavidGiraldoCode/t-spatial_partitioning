//
//  TestDerivedScene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-24.
//
#pragma once
#include <stdio.h>
#include "Scene.hpp"

class TestDerivedScene : public Scene
{
public:
    TestDerivedScene();
    ~TestDerivedScene();
    void setup() override;
    void update() override;
    void draw() override;
};
