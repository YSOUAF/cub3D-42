#include "cub3d.h"

// void draw_square(t_cub3d *cub, int x, int y, int color)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if (j == TILE_SIZE - 1 || i == TILE_SIZE - 1)
// 				mlx_put_pixel(cub->img.img, x + j, y + i, 0x000000);
// 			else
// 				mlx_put_pixel(cub->img.img, x + j, y + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void render_tiles(t_cub3d *cub)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (cub->map.data[i])
// 	{
// 		j = 0;
// 		while (cub->map.data[i][j])
// 		{
// 			if (cub->map.data[i][j] == '1')
// 				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFF2DD1);
// 			else if (cub->map.data[i][j] == '0')
// 				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFDFFB8);
// 			else
// 				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, 0);
// 			j++;
// 		}
// 		i++;
// 	}
// }

#include "cub3d.h"

static void	draw_player_dot(t_cub3d *cub)
{
	int	x;
	int	y;

	x = SIZE_MINIMAP_W / 2 - 4;
	while (x < SIZE_MINIMAP_W / 2 + 4)
	{
		y = SIZE_MINIMAP_H / 2 - 4;
		while (y < SIZE_MINIMAP_H / 2 + 4)
		{
			mlx_put_pixel(cub->img.img_mini, x, y, 0x799EFFFF);
			y++;
		}
		x++;
	}
}

static void	put_minimap_pixel(t_cub3d *cub, int x, int y,
	int in_x, int in_y)
{
	(void)cub;
	(void)in_x;
	(void)in_y;
	(void)y;
	(void)x;
	if (in_x < 0 || in_y < 0 || in_x > cub->map.width
		|| in_y > cub->map.height)
		mlx_put_pixel(cub->img.img_mini, x, y, 0xE3E3E3FF);
	else if (cub->map.data[in_y][in_x] == '1')
		mlx_put_pixel(cub->img.img_mini, x, y, 0x000000FF);
	else
		mlx_put_pixel(cub->img.img_mini, x, y, 0xE3E3E3FF);
}

static void	draw_minimap_grid(t_cub3d *cub, int x0, int y0)
{
	int	x;
	int	y;
	int	in_x;
	int	in_y;

	x = -1;
	while (++x < SIZE_MINIMAP_W)
	{
		y = -1;
		in_x = x0 + (x * 16 * TILE_SIZE) / SIZE_MINIMAP_W;
		in_x /= TILE_SIZE;
		while (++y < SIZE_MINIMAP_H)
		{
			in_y = y0 + (y * 8 * TILE_SIZE) / SIZE_MINIMAP_H;
			in_y /= TILE_SIZE;
			put_minimap_pixel(cub, x, y, in_x, in_y);
		}
	}
}

void	mini_map(t_cub3d *cub)
{
	int	x0;
	int	y0;

	x0 = cub->player.pos.x - 8 * TILE_SIZE;
	y0 = cub->player.pos.y - 4 * TILE_SIZE;
	draw_minimap_grid(cub, x0, y0);
	draw_player_dot(cub);
}

static void	draw_background(t_cub3d *cub)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (y <= WIN_H / 2)
				mlx_put_pixel(cub->img.img, x, y, cub->map.color_c);
			else
				mlx_put_pixel(cub->img.img, x, y, cub->map.color_f);
			y++;
		}
		x++;
	}
}

void	render_map(void *ptr)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)ptr;
	update_player_position(cub);
	draw_background(cub);
	cast_all_rays(cub);
	// mini_map(cub);
	mlx_image_to_window(cub->mlx, cub->img.img_mini, 50, 50);
	mlx_image_to_window(cub->mlx, cub->img.img, 0, 0);
}
