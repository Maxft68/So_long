/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/19 04:28:32 by mdsiurds         ###   ########.fr       */
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
	verif_rectangle(&game);
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
	game->fd = -1;
}

void	verif_rectangle(t_game *game)
{
	int len = -10;
	int temp = -10;
	char *line;
	int fd = open(game->name_map, O_RDONLY);

	ft_printf("len =%d\n", len);
	ft_printf("temp =%d\n", temp);
	ft_printf("fd =%d\n", fd);
	line = get_next_line(fd);
	ft_printf("linebeforeSF =%s\n", line);
	len = ft_strlen(line);
	ft_printf("line =%s\n", line);
	free(line);
	while (get_next_line(fd))
	{
		temp = ft_strlen(line);
		ft_printf("line =%s\n", line);
		ft_printf("len =%d\n", len);
		ft_printf("temp =%d\n", temp);
		if (temp != len)
		{
			ft_putstr_fd("Error\nPlease, use a rectangle map\n", 1); // remettre sur 2 a la fin
			free(line);
			exit(1);
		}	
		free(line);
	}
}
