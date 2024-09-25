//
//  Ray.hpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-25.
//  The Ray define the sensing mechanism of the agent
//
#pragma once
#include <stdio.h>
#include "ofVec3f.h"

class Ray
{
public:
    Ray():
        m_origin(0.0f, 0.0f, 0.0f),
        m_direction(0.0f, 0.0f, 0.0f){};
    Ray(const ofVec3f & origin, const ofVec3f & direction);
    ~Ray();
            void        setOrigin(const ofVec3f & origin);
            void        setDirection(const ofVec3f & direction);
    const   ofVec3f&    getIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction);
    const   ofVec3f&    getFirstIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction);
    const   float       getReach();
private:
    ofVec3f      m_origin;
    ofVec3f      m_direction;
    ofVec3f      m_firstIntersection;
    ofVec3f      m_newIntersection;
    float        reach = 400;
};
