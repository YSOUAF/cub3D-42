#include "cub3d.h"

// void	my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
// 		return ;
// 	dst = cub->img.addr + (y * cub->img.lines_len + x * (cub->img.bpp / 8));
// 	*(unsigned int *)dst = color;
// }

void	init_mlx(t_cub3d *cub)
{
	cub->mlx = mlx_init(WIN_W, WIN_H, "cube3d", false);

	// cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, WIN_W, WIN_H);
}



