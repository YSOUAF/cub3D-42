#include "cub3d.h"

void cast_ray(t_cub3d *cub, double ray_angle)
{
    t_point hor_hit, ver_hit;
    double hor_dis, ver_dis;
    int found_hor, found_ver;

    cub->ray.angle = ray_angle;
    cub->ray.hit_wall = 0;
    cub->ray.distance = max_ray_distance(ray_angle);
    cub->ray.is_vertical = 0;
    ray_angle = normlize_angle(ray_angle);
    hor_hit = find_hor_inter(cub, ray_angle, &found_hor);
    ver_hit = find_vert_inter(cub, ray_angle, &found_ver);
    hor_dis = 0;
    ver_dis = 0;
    if(found_hor)
        hor_dis = calculate_distance(cub->player.pos, hor_hit);
    if(found_ver)
        ver_dis = calculate_distance(cub->player.pos, ver_hit);
    if(found_hor &&( !found_ver || hor_dis < ver_dis))
    {
        cub->ray.distance = hor_dis;                                                                    
        cub->ray.hit_point = hor_hit;
        cub->ray.hit_wall = 1;
        cub->ray.is_vertical = 0;
        if(sin(ray_angle) < 0)
            cub->ray.drction = NORTH;
        else 
            cub->ray.drction = SOUTH;
    }
    else if(found_ver)
    {
        cub->ray.distance = ver_dis;
        cub->ray.hit_point = ver_hit;
        cub->ray.hit_wall = 1;
        cub->ray.is_vertical = 1;
        if(cos(ray_angle) > 0)
            cub->ray.drction = EAST;
        else 
            cub->ray.drction = WEST;
    }
}

void draw_ray(t_cub3d *cub, int x)
{
    double h;
    double d_ofwin;
    double angle_x;
    double d_towin;
    int top;
    int down;

    angle_x = fabs(cub->ray.angle - cub->player.angle);
    d_ofwin = fabs(x - (double)WIN_W / 2);
    d_towin = (WIN_W / 2) / tan(FOV / 2) / cos(angle_x);
    h = (d_towin * TILE_SIZE ) / cub->ray.distance;
    top = (WIN_H - h) / 2;
    down = (WIN_H + h) / 2;
    for (int y = 0; y < WIN_H; y++)
    {
        if (y >= top && y <= down)
        {
            if (cub->ray.drction == EAST)
                my_mlx_pixel_put(cub, x, y, 0x3E3F29);
            else if (cub->ray.drction == NORTH)
                my_mlx_pixel_put(cub, x, y, 0x57564F);
            else if (cub->ray.drction == SOUTH)
                my_mlx_pixel_put(cub, x, y, 0x7A7A73);
            else if (cub->ray.drction == WEST)
                my_mlx_pixel_put(cub, x, y, 0x0A400C);
        }
    }
}

void cast_all_rays(t_cub3d *cub)
{
    double ray_angle;
    double angle_step;

    angle_step = (double)(FOV/WIN_W);
    ray_angle = cub->player.angle - (FOV/2);
    double x= 0;
    while(x < WIN_W)
    {
        cast_ray(cub, ray_angle);
        draw_ray(cub, x);
        ray_angle+= angle_step;
        x++;
    }
}
