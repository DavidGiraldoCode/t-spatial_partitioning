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
    m_origin = origin;
}

void Ray::setDirection(const ofVec3f & direction)
{
    m_direction = direction;
}

const ofVec3f& Ray::getIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction)
{
    ofVec3f* intersectionPoint = new ofVec3f();
    
    return *intersectionPoint;
}

const ofVec3f& Ray::getFirstIntersectionPoint(const ofVec3f & origin, const ofVec3f & direction)
{
    m_newIntersection = ofVec3f(0,0,0);
    
    std::cout << "Ray starts at: [" << m_origin << "] - extends until: [" << m_direction * m_reach <<"]" << '\n';
    
    return m_newIntersection;
}

const ofVec3f&  Ray::getDirection() const
{
    return m_direction;
}

const ofVec3f&  Ray::getOrigin() const
{
    return m_origin;
}

const float Ray::getReach()
{
    return m_reach;
}

const bool Ray::intersectPlane(const ofVec3f &planeNormal,
                               const ofVec3f &planePosition,
                               const ofVec3f &rayOrigin,
                               const ofVec3f &rayDirection,
                               float &lambaT)
{
    float parallelCheck = planeNormal.dot(rayDirection);
    float PARALLEL_THRESHOLD = 0.00000009; // To avoid multiplying by 0;
    std::cout << planeNormal << " planeNormal \n";
    std::cout << rayDirection << " rayDirection \n";
    std::cout << parallelCheck << " parallelCheck \n";
    
    if(parallelCheck > PARALLEL_THRESHOLD || parallelCheck < PARALLEL_THRESHOLD * -1)
    {
        
        lambaT = -1 * (planeNormal.dot(planePosition + rayOrigin)) / parallelCheck;
        ofVec3f intersectionPoint = rayOrigin + rayDirection * lambaT;
        std::cout << intersectionPoint << " intersectionPoint \n";
        
        return (lambaT >= 0);
    }
    
    return false;
}
