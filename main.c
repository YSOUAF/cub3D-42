#include "cub3d.h"

int main(void)
{
    t_cub3d cub;

    cub.keys = (t_keys){0};
    init_map(&cub);
    init_player(&cub);
    init_mlx(&cub);
    setup_hooks(&cub);
    mlx_loop(cub.mlx);
    return (0);
}