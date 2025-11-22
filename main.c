#include "cub3d.h"

int find_player_position(t_map *map)
{
    int i;
    int j;
    int player_found;

    i = 0;
    player_found = 0;
    while (map->data[i])
    {
        j = 0;
        while (map->data[i][j])
        {
            if (map->data[i][j] == 'N' || map->data[i][j] == 'S' ||
                map->data[i][j] == 'E' || map->data[i][j] == 'W')
            {
                // Calculate pixel position (center of tile)
                map->posX = (j * TILE_SIZE) + (TILE_SIZE / 2.0);
                map->posY = (i * TILE_SIZE) + (TILE_SIZE / 2.0);
                
                // Set angle based on direction
                if (map->data[i][j] == 'N')
                    map->angle = 3 * M_PI_2;  // 270° (up)
                else if (map->data[i][j] == 'S')
                    map->angle = M_PI_2;       // 90° (down)
                else if (map->data[i][j] == 'E')
                    map->angle = 0;            // 0° (right)
                else if (map->data[i][j] == 'W')
                    map->angle = M_PI;         // 180° (left)
                
                // Replace player char with '0' (empty space)
                map->data[i][j] = '0';
                
                player_found = 1;
                break;
            }
            j++;
        }
        if (player_found)
            break;
        i++;
    }
    
    return (player_found);
}

void print_map(char **map_data)
{
    int i = 0;
    if (!map_data)
    {
        printf("map_data is NULL\n");
        return;
    }
    while (map_data[i])
    {
        printf("[%s]\n", map_data[i]);
        i++;
    }
    printf("-- end of map (%d lines) --\n", i);
}

void cleanup(t_cub3d *cub)
{
    if (cub->mlx)
    {
        if (cub->img.img)
            mlx_delete_image(cub->mlx, cub->img.img);
        mlx_terminate(cub->mlx);
    }
}

int main(int ac, char **av)
{
    t_map *map;
    t_cub3d cub;

    // Check arguments
    if (ac != 2 || !check_ext(av[1]))
        return (printf("Error:\ninvalid ext or num arg\n"), 1);

    // Allocate and initialize map structure
    map = malloc(sizeof(t_map));
    if (!map)
        return (printf("Error:\nallocation struct failed\n"), 1);
    ft_memset(map, 0, sizeof(t_map));

    // Parse map file
    if (!allocate_map(av[1], &map) || !map->height)
    {
        free(map);
        return (printf("Error:\ninvalid map - failed to load\n"), 1);
    }

    // Validate map
    if (!parss_map(map->data))
    {
        free(map);
        return (printf("Error:\ninvalid map - validation failed\n"), 1);
    }

    // Find player position and angle from map
    if (!find_player_position(map))
    {
        free(map);
        return (printf("Error:\nno player position found in map\n"), 1);
    }

    // Print map info for debugging
    printf("=== Map Info ===\n");
    printf("Width: %d\n", map->width);
    printf("Height: %d\n", map->height);
    printf("NO: %s\n", map->path_no ? map->path_no : "NULL");
    printf("SO: %s\n", map->path_so ? map->path_so : "NULL");
    printf("WE: %s\n", map->path_we ? map->path_we : "NULL");
    printf("EA: %s\n", map->path_ea ? map->path_ea : "NULL");
    printf("Floor color: 0x%08X\n", map->color_f);
    printf("Ceiling color: 0x%08X\n", map->color_c);
    printf("Player X: %.2f\n", map->posX);
    printf("Player Y: %.2f\n", map->posY);
    printf("Player Angle: %.2f rad (%.0f°)\n", map->angle, map->angle * 180 / M_PI);
    printf("=================\n");
    print_map(map->data);

    // Initialize cub3d structure
    ft_memset(&cub, 0, sizeof(t_cub3d));
    cub.map = *map;

    // Initialize player position and angle from map
    init_player(&cub);

    // Initialize MLX
    init_mlx(&cub);
    if (!cub.mlx)
    {
        free(map);
        return (printf("Error:\nMLX initialization failed\n"), 1);
    }

    // Setup hooks
    setup_hooks(&cub);

    // Start game loop
    mlx_loop(cub.mlx);

    // Cleanup
    cleanup(&cub);
    free(map);

    return (0);
}