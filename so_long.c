/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/20 10:36:06 by mdsiurds         ###   ########.fr       */
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
	fill_the_map(&game);
	close_all_array(&game);
	
}

void	ft_exit(char *error, t_game *game)
{
	ft_putstr_fd(error, 1); //remettre 2 a la fin
	close_all_array(game);
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
	game->map = NULL;
	game->map_to_check = NULL;
	game->nb_rainbow = -1;
	game->name_map = argv[1];
	game->nb_players = -1;
	game->fd = -1;
	game->len = -10;
	game->first_len = -10;
	game->game_line = 1;
}

void close_all_array(t_game *game)
{
	if (game->map)
		free_array(game->map);
	game->map = NULL;
	if (game->map_to_check)
		free_array(game->map_to_check);
	game->map_to_check = NULL;
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return ;
}

void	verif_rectangle(t_game *game)
{
	char *line;
	game->fd = open(game->name_map, O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nNot possible to open the map\n", 1);
		exit(1);
	}
	line = get_next_line(game->fd);
	if (!line)
		exit(1);
	game->first_len = ft_strlen(line);
	if (line[game->first_len - 1] == '\n')
			game->first_len--;
	free(line);
	while ((line = get_next_line(game->fd)))
	{
		if (!line)
			exit(1);
		game->game_line++;
		game->len = ft_strlen(line);
		if (line[game->len - 1] == '\n')
			game->len--;
		if (game->first_len != game->len)
		{
			ft_putstr_fd("Error\nPlease, use a rectangle map\n", 1); // remettre sur 2 a la fin
			free(line);
			exit(1);
		}
		free(line);
	}
	close(game->fd);
}

void print_map(char **map)
{
	int i;
	
	if (!map)
		return;
		
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
}
void	fill_the_map(t_game *game)
{
	char *map;
	int i;
	game->fd = open(game->name_map, O_RDONLY);
	if (game->fd == -1)
	{
		ft_putstr_fd("Error\nNot possible to open the map\n", 1);
		exit(1);
	}
	game->map = malloc(sizeof(char *) * (game->game_line + 1));
	if (!game->map)
		exit(1);
	game->map_to_check = malloc(sizeof(char *) * (game->game_line + 1));
	if (!game->map_to_check)
	{
		free_array(game->map);
		exit(1);
	}
	i = 0;
	map = get_next_line(game->fd);
	if (!map)
		exit(1);
	while (map)
	{
		game->map[i] = ft_strdup(map);
		game->map_to_check[i] = ft_strdup(map);
		i++;
		free(map);
		map = get_next_line(game->fd);
	}
	game->map[i] = NULL;
	game->map_to_check[i] = NULL;
	printf("\n\nmap\n");
	print_map(game->map);
	printf("\n\nmap_to_check\n");
	print_map(game->map_to_check);
}
