#pragma once
#include <math.h>
#include <algorithm>

struct Box
{
    float pos_x  = 0.0f;
    float pos_y  = 0.0f;
    float width  = 1.0f;
    float height = 1.0f;

    /** Detects intersection (overlap) between this Box and another Box instance.
    *   \param other is a reference to another Box instance to check for collision with
    *   \return true if the two boxes overlap
    */
    bool intersect(Box &other) 
    {
        return (fabs(pos_x - other.pos_x) * 2.0f < (width + other.width)) &&
            (fabs(pos_y - other.pos_y) * 2.0f < (height + other.height));
    }

    /** Detects an intersection when this Box is "above" (smaller y values) a target box (other)
    *   and reports the adjustment offset so that the two boxes are separated.
    *   
    *   \param other is the second (target) Box to test collision on the vertical axis with.
    *   \return the offset this Box needs to move in the y axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectDown(Box &other)
    {
        if (fabs(pos_x - other.pos_x) * 2.0f >= (width + other.width) || pos_y > other.pos_y)
            return 0.0f;
        return std::min<float>(0.0f, other.pos_y - (other.height / 2.0f) - pos_y - (height / 2.0f));
    }

    /** Detects a horizontal intersection this Box is beside a target box (other).
    *   and reports the adjustment offset so that the two boxes are separated.
    *  
    *   \param other is the second (target) Box to test collision on the horizontal axis with.
    *   \return the offset this Box needs to move in the x axis, so that it does not collide
    *   anymore with the target Box (other), or 0.0f if no collision is found.
    */
    float intersectSideways(Box &other)
    {
        if (fabs(pos_y - other.pos_y) * 2.0f >= (width + other.width))
            return 0.0f;
        if (pos_x > other.pos_x)
            return std::max<float>(0.0f, other.pos_x + (other.width / 2.0f) - pos_x + (width / 2.0f));
        else
            return std::min<float>(0.0f, other.pos_x - (other.width / 2.0f) - pos_x - (width / 2.0f));
    }
    
    /** Default ctor
    */
    Box() {}

    /** Basic Box ctor.
    *   \param x is the x coordinate of the box center
    *   \param y is the y coordinate of the box center
    *   \param w is the width of the box
    *   \param h is the height of the box
    */
    Box(float x, float y, float w, float h) 
        : pos_x(x), pos_y(y), width(w), height(h) {}
};

