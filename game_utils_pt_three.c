/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_pt_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 13:18:25 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/26 14:58:30 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	render_map_pt_two(t_game *game_data);

void	render_map(t_game *game_data)
{
	render_map_pt_two(game_data);
	mlx_put_image_to_window(game_data->mlx_ptr, game_data->mlx_window,
		game_data->player_active_texture, game_data->player_loc_x * PIXEL,
		game_data->player_loc_y * PIXEL);
}

static void	render_map_pt_two(t_game *g_d)
{
	int	x;
	int	y;

	y = 0;
	while (y < g_d->map_height)
	{
		x = 0;
		while (x < g_d->map_width)
		{
			if (g_d->map[y][x] == 'E')
				mlx_put_image_to_window(g_d->mlx_ptr, g_d->mlx_window,
					g_d->exit_texture, x * PIXEL, y * PIXEL);
			else if (g_d->map[y][x] == '1')
				mlx_put_image_to_window(g_d->mlx_ptr, g_d->mlx_window,
					g_d->wall_texture, x * PIXEL, y * PIXEL);
			else if (g_d->map[y][x] == 'C')
				mlx_put_image_to_window(g_d->mlx_ptr, g_d->mlx_window,
					g_d->collectible_texture, x * PIXEL, y * PIXEL);
			else if (g_d->map[y][x] != '1')
				mlx_put_image_to_window(g_d->mlx_ptr, g_d->mlx_window,
					g_d->background_texture, x * PIXEL, y * PIXEL);
			x++;
		}
		y++;
	}
}
