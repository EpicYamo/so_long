/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:13:48 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/19 14:13:48 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <unistd.h>

void	fail_exit(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	free_game_data(t_game *game_data, int line_count, int option)
{	
	while (line_count > 0)
	{
		free(game_data->map[line_count - 1]);
		line_count--;
	}
	if (option == 1)
		free(game_data->map);
	if (option == 2)
	{
		free(game_data->collectible_loc_x);
		free(game_data->collectible_loc_y);
		free(game_data->map);
	}
	if (option == 3)
	{
		free(game_data->collectible_loc_x);
		free(game_data->map);
	}
	free(game_data);
}

void	free_data_and_fail_exit(t_game *game_data, int line_count, int option)
{
	free_game_data(game_data, line_count, option);
	fail_exit();
}

int	exit_game(t_game *game_data)
{
	mlx_loop_end(game_data->mlx_ptr);
	mlx_destroy_image(game_data->mlx_ptr, game_data->exit_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->wall_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->collectible_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->background_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->player_left_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->player_right_texture);
	mlx_destroy_window(game_data->mlx_ptr, game_data->mlx_window);
	mlx_destroy_display(game_data->mlx_ptr);
	free(game_data->mlx_ptr);
	free_game_data(game_data, game_data->map_height, 2);
	exit(EXIT_SUCCESS);
}

void	ft_putnbr(int n)
{
	char	digit;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		ft_putnbr(n);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
		{
			digit = n + 48;
			write(1, &digit, 1);
		}
	}
}
