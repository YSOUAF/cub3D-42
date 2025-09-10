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

// void print_map(char **map_data)
// {
//     int i = 0;
//     if (!map_data)
//     {
//         printf("map_data is NULL\n");
//         return;
//     }
//     while (map_data[i])
//     {
//         printf("[%s]\n", map_data[i]);
//         i++;
//     }
//     printf("-- end of map (%d lines) --\n", i);
// }


// int main (int ac, char **av)
// {
//     if (ac != 2 || !check_ext(av[1]))
//         return (printf("hnaaa1\n"),1);
//     t_map *map = malloc(sizeof(t_map));
//     if (!map)
//         return (printf("hnaaa2\n"), 1);
//     map->width = 0;
//     map->height = 0;
//     if (!allocate_map(av[1], &map))
//         return (printf("hnaaa3\n"), 1);
//     printf("width => %d\n",map->width);
//     printf("height => %d\n",map->height);
//     print_map(map->data);
//     return (0);
// }