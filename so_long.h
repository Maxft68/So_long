/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxoph <maxoph@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:46:41 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 15:38:21 by maxoph           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft/libft.h"
# include "./libft/printf/ft_printf.h"
# include "./libft/gnl/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_image
{
	int		bidule;

	
	
}			t_image;

typedef struct s_game
{
	char	**map;
	char	**map_to_check;
	int		nb_rainbow;
	int		nb_players;
	int		fd;
	char	*name_map;
	int		len;
	int		first_len;
	int		game_line;
	
	t_image	*image;
	
}			t_game;



void	initialize(t_game *game, char **argv);
void	verif_name_map(char **argv);
void	verif_open(t_game *game, char **argv);
void	verif_rectangle(t_game *game);
void	fill_the_map(t_game *game);
void	free_array(char **array);
void	close_all_array(t_game *game);
void	print_map(char **map); // A SUPPRIMER A LA FIN
#endif