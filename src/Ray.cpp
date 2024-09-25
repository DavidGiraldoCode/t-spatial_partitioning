//
//  Ray.cpp
//  s-spatial_partitioning
//
//  Created by David MacBook on 2024-09-25.
//
#include "Ray.hpp"

//Public:
Ray::Ray(const ofVec3f & origin, const ofVec3f & direction)
{
    m_origin = origin;
    m_direction = direction;
}

Ray::~Ray()
{
}

void Ray::setOrigin(const ofVec3f & origin)
{
    
}

void Ray::setDirection(const ofVec3f & direction)
{
    
}

const ofVec3f& Ray::getIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction)
{
    ofVec3f* intersectionPoint = new ofVec3f();
    
    return *intersectionPoint;
}

const ofVec3f& Ray::getFirstIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction)
{
    m_newIntersection = ofVec3f(0,0,0);
    
    std::cout << "Ray starts at: [" << origin << "] - extends until: [" << direction <<"]" << '\n';
    
    return m_newIntersection;
}

const float Ray::getReach()
{
    return reach;
}
