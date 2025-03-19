/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 01:46:19 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	t_game game;
	if (argc != 2)
		return(1);
	verif_name_map(argv);
	initialize(&game, argv);
	verif_open(&game, argv);
}

void	verif_name_map(char **argv)
{
	int len;
	
	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nPlease, use a valid map\n", 1); // remettre sur 2 a la fin
		exit(1);
	}
}

void	verif_open(t_game *game, char **argv)
{
	game->fd = open(argv[1], O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nPlease, use a valid name\n", 1); // remettre sur 2 a la fin
		exit(1);
	}
}

void	initialize(t_game *game, char **argv)
{
	game->nb_rainbow = -1;
	game->name_map = argv[1];
	game->nb_players = -1;
}