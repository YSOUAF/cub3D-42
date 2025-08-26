#include "cub3d.h"

void draw_player_circle(t_cub3d *cub, int px, int py, int size)
{
    int i;
    int j;
    int x;
    int y;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            x = px - 10 + i;
            y = py - 10 + j;
            if (pow(x - px, 2) + pow(y - py, 2) <= pow(10, 2))
                my_mlx_pixel_put(cub, x, y, 0x660B05);
            j++;
        }
        i++;
    }
}
void draw_direction_line(t_cub3d *cub, int px, int py, int dis)
{
    int i;
    int line_x;
    int line_y;

    i = 0;
    while (i < dis)
    {
        line_x = px + cos(cub->player.angle) * i;
        line_y = py + sin(cub->player.angle) * i;
        my_mlx_pixel_put(cub, line_x, line_y, 0x0012FD00);
        i++;
    }
}
void draw_player(t_cub3d *cub)
{
    int px;
    int py;

    px = (int)(cub->player.pos.x);
    py = (int)(cub->player.pos.y);
    draw_player_circle(cub, px, py, 40);
    draw_direction_line(cub, px, py, 40);
}
void init_player(t_cub3d *cub)
{
    cub->player.angle = 60;
    cub->player.pos.x = 5.6 * TILE_SIZE;
    cub->player.pos.y = 12.5 * TILE_SIZE;
}

