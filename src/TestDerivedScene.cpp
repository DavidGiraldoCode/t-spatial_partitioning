//
//  TestDerivedScene.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-24.
//
#include "TestDerivedScene.hpp"

TestDerivedScene::TestDerivedScene()
{
    std::cout << "TestDerivedScene \n";
}

TestDerivedScene::~TestDerivedScene()
{
    std::cout << "Bye TestDerivedScene \n";
}

void TestDerivedScene::setup()
{
    Scene::setup(); //Recall the name -> scope resolution operator (::).
}

void TestDerivedScene::update()
{
    Scene::update();
}

void TestDerivedScene::draw()
{
    Scene::draw();
}
