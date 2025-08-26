#include "cub3d.h"

t_point find_vert_inter(t_cub3d *cub, double ray_angle, int *found_wall)
{
    t_point inter;
    t_point step;
    t_point current;
    t_point map;

    *found_wall = 0;
    inter.x = -1;
    inter.y = -1;

    current.x = floor(cub->player.pos.x / TILE_SIZE) * TILE_SIZE;
    if(is_ray_facing_right(ray_angle))
        current.x = floor(cub->player.pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    current.y = (tan(ray_angle) *(current.x - cub->player.pos.x)) + cub->player.pos.y;
    step.x = TILE_SIZE;
    if(is_ray_facing_left(ray_angle))
        step.x *= -1;
    step.y = step.x * tan(ray_angle);
    if (is_ray_facing_up(ray_angle) && step.y > 0)
        step.y *= -1;
    if (is_ray_facing_down(ray_angle) && step.y < 0)
        step.y *= -1;
    while(current.x >= 0 && current.x < WIN_W && current.y >= 0 && current.y < WIN_W)
    {
        map.x = (int)current.x /TILE_SIZE;
        map.y = (int)current.y /TILE_SIZE;

        if (is_ray_facing_left(ray_angle))
            map.x--;
        if(is_wall(cub, map.x, map.y))
        {
            inter.x = current.x;
            inter.y = current.y;
            *found_wall = 1;
            break;
        }
        current.x += step.x;
        current.y += step.y;
    }
    return inter;
}