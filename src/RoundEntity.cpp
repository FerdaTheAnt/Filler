#include "RoundEntity.hpp"

#include "GameArea.hpp"

#include <cmath>

RoundEntity::RoundEntity(float p_x, float p_y, float p_radius, float p_wall_elastic, float p_other_elastic)
:x(p_x), y(p_y), radius(p_radius), wall_elastic(p_wall_elastic), other_elastic(p_other_elastic)
{}

bool RoundEntity::detect_round_collision(RoundEntity &other)
{
    float min_allowed_dist = radius + other.radius;
    float dist = sqrt((other.x - x)*(other.x - x) + (other.y - y)*(other.y - y));

    return (dist< min_allowed_dist) ? true : false;
}

void RoundEntity::move()
{
    x += v_x;
    y += v_y;
}

void RoundEntity::resolve_boundary_collision(int width, int height, GameArea& border)
{
    //right
    if(x + radius > width - border.border_w)
    {
        x = width - radius - border.border_w;
        v_x *= -wall_elastic;
    }
    //left
    if(x - radius < border.border_w)
    {
        x = radius + border.border_w;
        v_x *= -wall_elastic;
    }
    //bottom
    if(y + radius > height - border.border_w + border.top)
    {
        y = height - radius - border.border_w + border.top;
        v_y *= -wall_elastic;
    }
    //top
    if(y-radius < border.border_w + border.top)
    {
        y = radius + border.border_w + border.top;
        v_y *= -wall_elastic;
    }
}

void RoundEntity::resolve_round_collision(RoundEntity &other)
{
    float min_allowed_dist = radius + other.radius;
    float dist_x = other.x - x;
    float dist_y = other.y - y;
    float norm = sqrt(dist_x*dist_x + dist_y*dist_y);
    float rel_v_x = other.v_x - v_x;
    float rel_v_y = other.v_y - v_y;

    double inv_total_mass = 1.0 / radius + 1.0 / other.radius;
    double impulse = -(1 + 0.5*(other_elastic + other.other_elastic)) * (rel_v_x * dist_x + rel_v_y * dist_y) / ( norm * inv_total_mass);

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