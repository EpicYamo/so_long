/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_pt_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:14:45 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/08 15:04:31 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <unistd.h>

static void	load_textures(t_game *game_data);
static void	check_textures(t_game *game_data);

void	run_game(t_game *game_data)
{
	game_data->mlx_ptr = mlx_init();
	if (!game_data->mlx_ptr)
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	game_data->mlx_window = mlx_new_window(game_data->mlx_ptr,
			game_data->map_width * PIXEL, game_data->map_height * PIXEL,
			"so_long");
	if (!game_data->mlx_window)
	{
		mlx_destroy_display(game_data->mlx_ptr);
		free(game_data->mlx_ptr);
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	}
	load_textures(game_data);
	render_map(game_data);
	game_loop(game_data);
}

static void	load_textures(t_game *game_data)
{
	int	width;
	int	height;

	game_data->background_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/background.xpm", &width, &height);
	game_data->exit_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/exit.xpm", &width, &height);
	game_data->collectible_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/collectible.xpm", &width, &height);
	game_data->player_right_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/player_right.xpm", &width, &height);
	game_data->player_left_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/player_left.xpm", &width, &height);
	game_data->wall_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/wall.xpm", &width, &height);
	game_data->player_active_texture = game_data->player_right_texture;
	check_textures(game_data);
}

static void	check_textures(t_game *g_d)
{
	if (!g_d->background_texture || !g_d->exit_texture
		|| !g_d->collectible_texture || !g_d->player_right_texture
		|| !g_d->player_left_texture || !g_d->wall_texture)
	{
		if (g_d->collectible_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->collectible_texture);
		if (g_d->wall_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->wall_texture);
		if (g_d->background_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->background_texture);
		if (g_d->player_left_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->player_left_texture);
		if (g_d->player_right_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->player_right_texture);
		if (g_d->exit_texture)
			mlx_destroy_image(g_d->mlx_ptr, g_d->exit_texture);
		mlx_destroy_window(g_d->mlx_ptr, g_d->mlx_window);
		mlx_destroy_display(g_d->mlx_ptr);
		free(g_d->mlx_ptr);
		free_game_data(g_d, g_d->map_height, 2);
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}
