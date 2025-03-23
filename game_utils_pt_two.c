/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_pt_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:40:09 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/23 17:40:09 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

static void	render_map_pt_two(t_game *game_data);

void	event_handler(int move_flag, t_game *game_data)
{
	int	i;
	int	h;

	i = 0;
	if (game_data->map[game_data->player_loc_y][game_data->player_loc_x] == 'C')
	{
		game_data->map[game_data->player_loc_y][game_data->player_loc_x] = '0';
		game_data->collectible_count--;
		if (game_data->collectible_count == 0)
		{
			mlx_destroy_image(game_data->mlx_ptr, game_data->exit_texture);
			game_data->exit_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
					"textures/exiton.xpm", &i, &h);
		}
	}
	if (game_data->collectible_count == 0
		&& game_data->map[game_data->player_loc_y][game_data->player_loc_x] == 'E')
		exit_game(game_data);
	if (move_flag != 0)
	{
		game_data->move_count++;
		ft_putnbr(game_data->move_count);
		write(1, "\n", 1);
	}
}

int	render_map(t_game *game_data)
{
	render_map_pt_two(game_data);
	mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window, game_data->player_active_texture,
		game_data->player_loc_x * PIXEL, game_data->player_loc_y * PIXEL);
	return (0);
}

static void	render_map_pt_two(t_game *game_data)
{
	int	x;
	int	y;

	y = 0;
	while (y < game_data->map_height)
	{
		x = 0;
		while (x < game_data->map_width)
		{
			mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window,
				game_data->background_texture, x * PIXEL, y * PIXEL);
			if (game_data->map[y][x] == 'E')
				mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window,
					game_data->exit_texture, x * PIXEL, y * PIXEL);
			else if (game_data->map[y][x] == '1')
				mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window,
					game_data->wall_texture, x * PIXEL, y * PIXEL);
			else if (game_data->map[y][x] == 'C')
				mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window,
					game_data->collectible_texture, x * PIXEL, y * PIXEL);
			x++;
		}
		y++;
	}
}
