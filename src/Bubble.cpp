#include "Bludger.hpp"

#include <cmath>

#include "Bubble.hpp"

const float PI = 3.14159265;

Bubble::Bubble(float p_x, float p_y, float p_radius)
    :x(p_x), y(p_y), radius(p_radius)
{

}

void Bubble::grow()
{
    if(growing)
    {
        this->radius++;
    }
}

void Bubble::pop()
{
    this->radius = 0;
}

float Bubble::getArea()
{
    return PI*radius*radius;
}

void Bubble::move()
{
    if(!growing)
    {
        x += v_x;
        y += v_y;
        v_y += gravity;
    }
}

void Bubble::resolveBoundaryCollision(int width, int height, int border)
{
    if (growing && (2*radius > width - 2*border || 2*radius > height - 2*border)) {
        stopGrowth();
    }
    //right
    if(x + radius > width - border)
    {
        x = width - radius - border;
        v_x *= -friction;
    }
    //left
    if(x - radius < border)
    {
        x = radius + border;
        v_x *= -friction;
    }
    //bottom
    if(y + radius > height - border + 100)
    {
        y = height - radius - border + 100;
        v_y *= -friction;
    }
    //top
    if(y-radius < border + 100)
    {
        y = radius + border + 100;
        v_y *= -friction;
    }
}

void Bubble::resolveBubbleCollision(Bubble &other)
{
    if(!detectRoundObjCollision(other.x, other.y, other.radius))
        return;

    if(growing)
    {
        stopGrowth();
        return;
    }
    if(other.growing)
    {
        other.stopGrowth();
        return;
    }
    
    float min_allowed_dist = radius + other.radius;
    float dist_x = other.x - x;
    float dist_y = other.y - y;
    float norm = sqrt(dist_x*dist_x + dist_y*dist_y);
    float rel_v_x = other.v_x - v_x;
    float rel_v_y = other.v_y - v_y;

    double inv_total_mass = 1.0 / radius + 1.0 / other.radius;
    double impulse = -(1 + elasticity) * (rel_v_x * dist_x + rel_v_y * dist_y) / ( norm * inv_total_mass);

    other.v_x += dist_x * impulse / (norm * other.radius);
    other.v_y += dist_y * impulse / (norm * other.radius);

    v_x -= dist_x * impulse / (norm *  radius);
    v_y -= dist_y * impulse / (norm *  radius);

    float penetration = min_allowed_dist - norm;
    
    other.x += (dist_x / norm) * penetration / (other.radius * inv_total_mass);
    other.y += (dist_y / norm) * penetration / (other.radius * inv_total_mass);

    x -= (dist_x / norm) * penetration / (radius * inv_total_mass);
    y -= (dist_y / norm) * penetration / (radius * inv_total_mass);
}

void resolveBludgerCollision(Bludger& bludger)
{
    //TODO
}

SDL_Rect Bubble::get_dst_rect()
{
    //decimal numbers chose in order to fit the texture better
    dst_rect.x = x - 1.06*radius;
    dst_rect.y = y - 1.06*radius;
    dst_rect.h = 2.12*radius;
    dst_rect.w = 2.12*radius;

    return dst_rect;
}

SDL_Rect Bubble::get_src_rect()
{
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.h = 680;
    src_rect.w = 680;

    return src_rect;
}

bool Bubble::detectRoundObjCollision(float other_x, float other_y, float other_radius)
{
    float min_allowed_dist = radius + other_radius;
    float dist = sqrt((other_x - x)*(other_x - x) + (other_y - y)*(other_y - y));

    return (dist< min_allowed_dist) ? true : false;
}