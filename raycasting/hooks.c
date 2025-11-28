#include "cub3d.h"

void key_press(mlx_key_data_t keydata, void* ptr)
{
    t_cub3d *cub = ptr;
    
    // Handle key press (when key is pressed down)
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
            cub->keys.w = 1;
        else if (keydata.key == MLX_KEY_S)
            cub->keys.s = 1;
        else if (keydata.key == MLX_KEY_A)
            cub->keys.a = 1;
        else if (keydata.key == MLX_KEY_D)
            cub->keys.d = 1;
        else if (keydata.key == MLX_KEY_UP)
            cub->keys.up = 1;
        else if (keydata.key == MLX_KEY_DOWN)
            cub->keys.down = 1;
        else if (keydata.key == MLX_KEY_LEFT)
            cub->keys.left = 1;
        else if (keydata.key == MLX_KEY_RIGHT)
            cub->keys.right = 1;
        else if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(cub->mlx);
    }
    // Handle key release (when key is released)
    else if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W)
            cub->keys.w = 0;
        else if (keydata.key == MLX_KEY_S)
            cub->keys.s = 0;
        else if (keydata.key == MLX_KEY_A)
            cub->keys.a = 0;
        else if (keydata.key == MLX_KEY_D)
            cub->keys.d = 0;
        else if (keydata.key == MLX_KEY_UP)
            cub->keys.up = 0;
        else if (keydata.key == MLX_KEY_DOWN)
            cub->keys.down = 0;
        else if (keydata.key == MLX_KEY_LEFT)
            cub->keys.left = 0;
        else if (keydata.key == MLX_KEY_RIGHT)
            cub->keys.right = 0;
    }
}

void close_hook(void* ptr)
{
    t_cub3d *cub = ptr;
    mlx_close_window(cub->mlx);
}

void setup_hooks(t_cub3d *cub)
{
    // Key hook for keyboard input
    mlx_key_hook(cub->mlx, key_press, cub);
    
    // Loop hook for continuous rendering
    mlx_loop_hook(cub->mlx, render_map, cub);
    
    // Close hook (optional, ESC already handled in key_press)
    mlx_close_hook(cub->mlx, close_hook, cub);

}