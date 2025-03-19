/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:46:41 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 00:30:26 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft/libft.h"
# include "./libft/printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_image
{
	int		bidule;

	
	
}			t_image;

typedef struct s_game
{
	int		nb_rainbow;
	int		nb_players;
	int		fd;
	char	*name_map;
	
	t_image	*image;
	
}			t_game;



void	initialize(t_game *game, char **argv);
void	verif_name_map(char **argv);
void	verif_open(t_game *game, char **argv);


#endif