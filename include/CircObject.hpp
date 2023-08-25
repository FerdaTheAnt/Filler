#pragma once

class CircObject
{
public:
    CircObject(float p_x, float p_y, float p_radius, float p_v_x=0, float p_v_y=0);
    virtual void move() = 0;
    virtual void collide() = 0;
    bool detectCollision();
protected:
    float x, y, radius;
    float v_x, v_y;
    //bool colliding;
};