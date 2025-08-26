#include "cub3d.h"

int is_valid_position(t_cub3d *cub, double new_x, double new_y)
{
    int player_x;
    int player_y;

    player_x = (int)new_x;
    player_y = (int)new_y;
    if (is_wall(cub, (player_x - COLLISION_WALL) / TILE_SIZE,
                (player_y - COLLISION_WALL) / TILE_SIZE))
        return (0);
    if (is_wall(cub, (player_x + COLLISION_WALL) / TILE_SIZE,
                (player_y - COLLISION_WALL) / TILE_SIZE))
        return (0);
    if (is_wall(cub, (player_x - COLLISION_WALL) / TILE_SIZE,
                (player_y + COLLISION_WALL) / TILE_SIZE))
        return (0);
    if (is_wall(cub, (player_x + COLLISION_WALL) / TILE_SIZE,
                (player_y + COLLISION_WALL) / TILE_SIZE))
        return (0);
    return (1);
}
void handle_forward_backward(t_cub3d *cub, double *new_x, double *new_y)
{
    if (cub->keys.up || cub->keys.w)
    {
        *new_x += cos(cub->player.angle) * MOVE_SPEED;
        *new_y += sin(cub->player.angle) * MOVE_SPEED;
    }
    if (cub->keys.down || cub->keys.s)
    {
        *new_x -= cos(cub->player.angle) * MOVE_SPEED;
        *new_y -= sin(cub->player.angle) * MOVE_SPEED;
    }
}
void handle_strafe(t_cub3d *cub, double *new_x, double *new_y)
{
    if (cub->keys.a)
    {
        *new_x += cos(cub->player.angle - M_PI_2) * MOVE_SPEED;
        *new_y += sin(cub->player.angle - M_PI_2) * MOVE_SPEED;
    }
    if (cub->keys.d)
    {
        *new_x += cos(cub->player.angle + M_PI_2) * MOVE_SPEED;
        *new_y += sin(cub->player.angle + M_PI_2) * MOVE_SPEED;
    }
}
void handle_rotation(t_cub3d *cub)
{
    if (cub->keys.left)
    {
        cub->player.angle -= ROTATE_SPEED;
        if (cub->player.angle < 0)
            cub->player.angle += 2 * M_PI;
    }
    if (cub->keys.right)
    {
        cub->player.angle += ROTATE_SPEED;
        if (cub->player.angle >= 2 * M_PI)
            cub->player.angle -= 2 * M_PI;
    }
}
void update_player_position(t_cub3d *cub)
{
    double new_x;
    double new_y;
    double temp_x;
    double temp_y;

    new_x = cub->player.pos.x;
    new_y = cub->player.pos.y;
    temp_x = new_x;
    temp_y = new_y;
    handle_forward_backward(cub, &new_x, &new_y);
    handle_strafe(cub, &new_x, &new_y);
    handle_rotation(cub);
    if (is_valid_position(cub, new_x, temp_y))
        cub->player.pos.x = new_x;
    if (is_valid_position(cub, temp_x, new_y))
        cub->player.pos.y = new_y;
}

