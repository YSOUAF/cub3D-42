#include "cub3d.h"

double normlize_angle(double angle)
{
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

double calculate_distance(t_point p1, t_point p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int is_wall(t_cub3d *cub, int map_x, int map_y)
{
    if (map_x < 0 || map_x >= cub->map.width ||
        map_y < 0 || map_y >= cub->map.height)
        return (1);
    return (cub->map.data[map_y][map_x] == '1');
}