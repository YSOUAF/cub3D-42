#include <stdlib.h>
#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define TILE_SIZE 32
#define WIN_W (50 * TILE_SIZE)
#define WIN_H (20 * TILE_SIZE)
#define ESC 53

typedef struct s_data
{
	void *img;
	char *addr;
	int bpp;
	int lines_len;
	int end;
} t_data;

typedef struct point
{
	double x;  // Changed to double for smoother movement
	double y;  // Changed to double for smoother movement
} t_point;

typedef struct player
{
	t_point pos;
	double angle;
} t_player;

typedef struct map
{
	char **data;
	int width;
	int height;
} t_map;

typedef struct cub3d
{
	t_player player;
	void *mlx;
	void *win;
	t_map map;
	t_data img;
} t_cub3d;

void my_mlx_pixel_put(t_cub3d *cub, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return;
	dst = cub->img.addr + (y * cub->img.lines_len + x * (cub->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_square(t_cub3d *cub, int x, int y, int color)
{
	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			my_mlx_pixel_put(cub, x + j, y + i, color);
		}
	}
}

void draw_player(t_cub3d *cub)
{
	int px = (int)(cub->player.pos.x * TILE_SIZE);
	int py = (int)(cub->player.pos.y * TILE_SIZE);

	// Draw player as a red square
	for (int i = TILE_SIZE / 4; i < 3 * TILE_SIZE / 4; i++)
	{
		for (int j = TILE_SIZE / 4; j < 3 * TILE_SIZE / 4; j++)
		{
			my_mlx_pixel_put(cub, px + j, py + i, 0xFF0000);
		}
	}
	
	// Draw direction line to show where player is facing
	int line_length = TILE_SIZE / 2;
	int end_x = px + TILE_SIZE/2 + (int)(cos(cub->player.angle) * line_length);
	int end_y = py + TILE_SIZE/2 + (int)(sin(cub->player.angle) * line_length);
	
	// Simple line drawing (Bresenham-like)
	int dx = abs(end_x - (px + TILE_SIZE/2));
	int dy = abs(end_y - (py + TILE_SIZE/2));
	int steps = (dx > dy) ? dx : dy;
	
	if (steps > 0)
	{
		float x_inc = (float)(end_x - (px + TILE_SIZE/2)) / steps;
		float y_inc = (float)(end_y - (py + TILE_SIZE/2)) / steps;
		
		for (int i = 0; i <= steps; i++)
		{
			int x = (px + TILE_SIZE/2) + (int)(i * x_inc);
			int y = (py + TILE_SIZE/2) + (int)(i * y_inc);
			my_mlx_pixel_put(cub, x, y, 0x00FF00); // Green line for direction
		}
	}
}

void render_map(t_cub3d *cub3d)
{
	for (int i = 0; cub3d->map.data[i]; i++)
	{
		for (int j = 0; cub3d->map.data[i][j]; j++)
		{
			if (cub3d->map.data[i][j] == '1')
				draw_square(cub3d, j * TILE_SIZE, i * TILE_SIZE, 0x102E50);
			else if (cub3d->map.data[i][j] == '0')
				draw_square(cub3d, j * TILE_SIZE, i * TILE_SIZE, 0xF3E9DC);
			else
				draw_square(cub3d, j * TILE_SIZE, i * TILE_SIZE, 0xF3E9DC);
		}
	}
	draw_player(cub3d);
}

#define UP 126
#define W 13
#define DOWN 125
#define S 1
#define LEFT 123
#define A 0
#define RIGHT 124
#define D 2
#define Q 12  // Rotate left
#define E 14  // Rotate right
#define PI 3.14159265358979323846

#define MOVE_SPEED 0.2
#define ROTATE_SPEED 0.1

int key_hook(int keycode, t_cub3d *cub)
{
	double new_x = cub->player.pos.x;
	double new_y = cub->player.pos.y;
	
	if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		exit(0);
	}
	
	// Movement based on player's current angle
	if (keycode == UP || keycode == W) // Forward
	{
		new_x += cos(cub->player.angle) * MOVE_SPEED;
		new_y += sin(cub->player.angle) * MOVE_SPEED;
	}
	else if (keycode == DOWN || keycode == S) // Backward
	{
		new_x -= cos(cub->player.angle) * MOVE_SPEED;
		new_y -= sin(cub->player.angle) * MOVE_SPEED;
	}
	else if (keycode == LEFT || keycode == A) // Strafe left
	{
		new_x += cos(cub->player.angle - PI/2) * MOVE_SPEED;
		new_y += sin(cub->player.angle - PI/2) * MOVE_SPEED;
	}
	else if (keycode == RIGHT || keycode == D) // Strafe right
	{
		new_x += cos(cub->player.angle + PI/2) * MOVE_SPEED;
		new_y += sin(cub->player.angle + PI/2) * MOVE_SPEED;
	}
	
	// Rotation
	if (keycode == Q) // Rotate left
	{
		cub->player.angle -= ROTATE_SPEED;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
	}
	else if (keycode == E) // Rotate right
	{
		cub->player.angle += ROTATE_SPEED;
		if (cub->player.angle >= 2 * PI)
			cub->player.angle -= 2 * PI;
	}

	// Check bounds and wall collisions for movement
	if (new_x != cub->player.pos.x || new_y != cub->player.pos.y)
	{
		if (new_x >= 0 && new_x < cub->map.width &&
			new_y >= 0 && new_y < cub->map.height &&
			cub->map.data[(int)new_y][(int)new_x] != '1')
		{
			cub->player.pos.x = new_x;
			cub->player.pos.y = new_y;
		}
	}

	// Always redraw (for rotation updates too)
	mlx_clear_window(cub->mlx, cub->win);
	render_map(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);

	return (0);
}

int close_hook(t_cub3d *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	exit(0);
	return (0);
}

int main(int argc, char const *argv[])
{
	t_cub3d cub3d;
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

	cub3d.map.data = map_data;
	cub3d.map.width = 50;
	cub3d.map.height = 20;
	cub3d.player.angle = 60; // Start facing right
	cub3d.player.pos.x = 20.5; // Center of tile
	cub3d.player.pos.y = 10.5; // Center of tile

	cub3d.mlx = mlx_init();
	if (!cub3d.mlx)
	{
		printf("Error: MLX initialization failed\n");
		return (1);
	}
	
	cub3d.win = mlx_new_window(cub3d.mlx, WIN_W, WIN_H, "cub3D");
	if (!cub3d.win)
	{
		printf("Error: Window creation failed\n");
		return (1);
	}
	
	cub3d.img.img = mlx_new_image(cub3d.mlx, WIN_W, WIN_H);
	if (!cub3d.img.img)
	{
		printf("Error: Image creation failed\n");
		return (1);
	}
	
	cub3d.img.addr = mlx_get_data_addr(cub3d.img.img, &cub3d.img.bpp, &cub3d.img.lines_len, &cub3d.img.end);

	// Initial render
	render_map(&cub3d);
	
	// Set up hooks
	mlx_key_hook(cub3d.win, key_hook, &cub3d);
	mlx_hook(cub3d.win, 17, 0, close_hook, &cub3d);
	
	mlx_put_image_to_window(cub3d.mlx, cub3d.win, cub3d.img.img, 0, 0);
	mlx_loop(cub3d.mlx);

	return 0;
}