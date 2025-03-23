/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:29 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/19 14:14:29 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFFER_SIZE 42
# define PIXEL 64
# define CLOSE_WINDOW 17
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

# include <stddef.h>
# include "minilibx-linux/mlx.h"

typedef struct s_game
{
	char	**map;
	int		map_width;
	int		map_height;
	int		player_loc_x;
	int		player_loc_y;
	int		exit_loc_x;
	int		exit_loc_y;
	int		collectible_count;
	int		*collectible_loc_x;
	int		*collectible_loc_y;
	void	*mlx_ptr;
	void	*mlx_window;
	void	*player_right_texture;
	void	*player_left_texture;
	void	*player_active_texture;
	void	*exit_texture;
	void	*background_texture;
	void	*collectible_texture;
	void	*wall_texture;
	int		move_count;
}t_game;

typedef struct s_count_variables
{
	int	exit_count;
	int	collectible_count;
}t_count_variables;

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
char	*ft_strchr(const char *s, int c);
int		ft_count_to_end_of_line(char *left_c);
char	*ft_check_newline_existence(char *left_c);
char	*ft_strjoin_modified(char *left_c, char *tmp);
void	fail_exit(void);
void	fill_map(t_game *game_data, char **argv);
int		count_lines(char *file_path, t_game *game_data);
void	free_game_data(t_game *game_data, int line_count, int option);
void	free_data_and_fail_exit(t_game *game_data, int line_count, int option);
void    check_and_finish_map(t_game *game_data, int line_count);
void	check_forbidden_elements(t_game *game_data, int line_count);
void	fill_map_element_info(t_game *game_data, int line_count);
void	fill_map_element_info_pt_four(t_game *game_data);
void	check_element_reachability(t_game *game_data);
void	run_game(t_game *game_data);
int		exit_game(t_game *game_data);
void	ft_putnbr(int n);
void	event_handler(int move_flag, t_game *game_data);
int		render_map(t_game *game_data);

#endif
