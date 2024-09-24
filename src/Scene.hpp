//
//  Scene.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-24.
//

#pragma once
#include <stdio.h>
#include <string>

class Scene
{
public:
    Scene();
    ~Scene();
    void setup();
    void update();
    void draw();
    void pressedEvents();
};
