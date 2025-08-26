#include "cub3d.h"

void	init_map(t_cub3d *cub)
{
	static char *map_data[] = {
		"11111111111111111111111111111111111111111111111111",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000011111000000000000000000000001",
		"10000000000000000000010001000000000000000000000001",
		"10000011111100000000011111000000001111000000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000010000100000000000000000000001000100000000001",
		"10000011111100000000000000000000001111000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000011111110000000000000000000001",
		"10000000000000000000010000010000000000000000000001",
		"10000000000000000000010000010000000000000000000001",
		"10000000000000000000011111110000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"10000000000000000000000000111000000000000000000001",
		"10000000000000000000000000000000000000000000000001",
		"11111111111111111111111111111111111111111111111111",
		NULL};

	cub->map.data = map_data;
	cub->map.width = 50;
	cub->map.height = 20;
}
void draw_square(t_cub3d *cub, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            if (j == TILE_SIZE - 1 || i == TILE_SIZE - 1)
                my_mlx_pixel_put(cub, x + j, y + i, 0x000000);
            else
                my_mlx_pixel_put(cub, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void	render_tiles(t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map.data[i])
	{
		j = 0;
		while (cub->map.data[i][j])
		{
			if (cub->map.data[i][j] == '1')
				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFF2DD1);
			else if (cub->map.data[i][j] == '0')
				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFDFFB8);
            else 
                draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0);
			j++;
		}
		i++;
	}
}
int	render_map(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	update_player_position(cub);
	render_tiles(cub);
	draw_player(cub);
	for (size_t x = 0; x < WIN_W; x++)
	{
		for (size_t y = 0; y < WIN_H; y++)
		{
			if (y <= WIN_H / 2)
				my_mlx_pixel_put(cub, x , y, 0x56DFCF);
			else
				my_mlx_pixel_put(cub, x , y, 0x541212);
		}
	}
	cast_all_rays(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}