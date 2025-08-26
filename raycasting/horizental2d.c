#include "cub3d.h"

t_point find_hor_inter(t_cub3d *cub, double ray_angle, int *found_wall)
{
    t_point inter;
    t_point step;
    t_point current;
    t_point map;

    *found_wall = 0;
    inter.x = -1;
    inter.y = -1;
    current.y = floor(cub->player.pos.y / TILE_SIZE) * TILE_SIZE;
    if(is_ray_facing_down(ray_angle))
        current.y = floor(cub->player.pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    current.x = cub->player.pos.x + (current.y - cub->player.pos.y) / tan(ray_angle);
    step.y = TILE_SIZE;
    if(is_ray_facing_up(ray_angle))
        step.y *= -1;
    step.x = step.y / tan(ray_angle);
    if(is_ray_facing_left(ray_angle) && step.x > 0)
        step.x *= -1;
    if(is_ray_facing_right(ray_angle) && step.x < 0)
        step.x *= -1;
    while (current.x >= 0 && current.x < WIN_W && current.y >= 0 && current.y < WIN_W)
    {
        map.x = (int)current.x / TILE_SIZE;
        map.y = (int)current.y / TILE_SIZE;
        if(is_ray_facing_up(ray_angle))
            map.y--;
        if(is_wall(cub,map.x, map.y))
        {
            inter.x = current.x;
            inter.y = current.y;
            *found_wall = 1;
            break;
        }
        current.x += step.x;
        current.y += step.y;
    }
    return(inter);
}
