#include "cub3d.h"

double max_ray_distance(double angle)
{
    return ((double)(WIN_W / 2) / tan(angle));
}

int is_ray_facing_down(double angle)
{
    return (angle > 0 && angle < M_PI);
}

int is_ray_facing_up(double angle)
{
    return !is_ray_facing_down(angle);
}

int is_ray_facing_right(double angle)
{
    return (angle < (0.5 * M_PI) || angle > (1.5 * M_PI));
}

int is_ray_facing_left(double angle)
{
    return !is_ray_facing_right(angle);
}