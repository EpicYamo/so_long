/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_pt_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:48:54 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/07 16:11:58 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	fill_map_pt_two(t_game *game_data, char **argv, int line_count);
static void	fill_map_pt_three(t_game *game_data);

void	fill_map(t_game *game_data, char **argv)
{
	size_t	line_count;

	line_count = count_lines(argv[1], game_data);
	if (line_count < 3)
		free_data_and_fail_exit(game_data, 0, 0);
	game_data->map = malloc(sizeof(char *) * (line_count + 1));
	if (!game_data->map)
		free_data_and_fail_exit(game_data, 0, 0);
	fill_map_pt_two(game_data, argv, line_count);
	fill_map_pt_three(game_data);
}

int	count_lines(char *file_path, t_game *game_data)
{
	char	*line;
	size_t	line_count;
	int		file_end_flag;
	int		fd;

	line_count = 0;
	file_end_flag = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		free_data_and_fail_exit(game_data, 0, 0);
	while (file_end_flag == 0)
	{
		line = get_next_line(fd);
		if (!line)
			file_end_flag = 1;
		if (line)
			line_count++;
		if (line)
			free(line);
	}
	close(fd);
	return (line_count);
}

static void	fill_map_pt_two(t_game *game_data, char **argv, int line_count)
{
	int		i;
	int		fd;
	int		j;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		free_data_and_fail_exit(game_data, 0, 1);
	while (line_count > 0)
	{
		game_data->map[i] = get_next_line(fd);
		if (!game_data->map[i])
			free_data_and_fail_exit(game_data, i - 1, 1);
		line_count--;
		i++;
	}
	j = 0;
	while (game_data->map[i - 1][j])
		j++;
	if (game_data->map[i - 1][j - 1] == '\n')
		game_data->map[i] = get_next_line(fd);
	else
		game_data->map[i] = NULL;
	close(fd);
}

static void	fill_map_pt_three(t_game *game_data)
{
	int	i;
	int	j;

	i = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
			j++;
		if (game_data->map[i][j - 1] == '\n')
			game_data->map[i][j - 1] = '\0';
		i++;
	}
}
