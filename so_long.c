/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:44:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/20 12:07:24 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize(t_game *game, char **argv)
{
	game->map = NULL;
	game->map_to_check = NULL;
	game->name_map = argv[1];
	game->fd = -1;
	game->len = -10;
	game->first_len = -10;
	game->game_line = 1;
	game->nb_rainbow = 0;
	game->nb_players = 0;
	game->nb_unicorn = 0;
	game->pos_x = -1;
	game->pos_y = -1;
}

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
	verif_p_c_e(&game);


	
	close_all_array(&game);
}

int	is_p_c_e(char test)
{
	if (test == 'P' || test == 'C' || test == 'E')
		return(1);
	else if (test)
	return(0);
}

void	verif_p_c_e(t_game *game)
{
	int i;
	int j;
	
	i = -1;
	while(++i, game->map[i])
	{
		j = -1;
		while(++j, game->map[i][j])
		{
			if(is_p_c_e(game->map[i][j]) == 1)
			{
				if (game->map[i][j] == 'P')
				{
					game->nb_players++;
					game->pos_x = j;
					game->pos_y = i;
				}
				else if (game->map[i][j] == 'C')
					game->nb_rainbow++;
				else if (game->map[i][j] == 'E')
					game->nb_unicorn++;
			}
		}
	}
	printf("pos x =%d pos y =%d\n", game->pos_x, game->pos_y);
	printf("nb players= %d\n", game->nb_players);
	printf("nb rainbow = %d\n", game->nb_rainbow);
	printf("nb unicorn = %d\n", game->nb_unicorn);
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
