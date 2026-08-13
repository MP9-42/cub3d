/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:35 by MP9               #+#    #+#             */
/*   Updated: 2026/08/13 14:56:38 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// initialise the cub struct and start parsing of the .cub file
void	init_cub(char **argv, t_cub *cub, t_parsing *parsing)
{
	parsing->fd = open(argv[1], O_RDONLY);
	if (parsing->fd < 0)
		exit(1);
	readfile(parsing);
	if (!parsing->file)
		exit(1);
	parsing->file_len = 0;
	while (parsing->file[parsing->file_len])
		parsing->file_len++;
	cub->parsing = parsing;
	cub->map = get_map(cub, parsing);
	if (!validate_map(cub->map))
		error_exit(2);
	cub->total_cans = count_total_cans(cub->map);
	cub->game = ft_calloc(1, sizeof(t_game));
	cub->player = init_player(cub->map);
	cub->npc = init_npc(cub->map);
	cub->game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
}

void	mlx_loops(t_cub *cub)
{
	int32_t	temp;

	get_image(cub->game, cub);
	mlx_set_cursor_mode(cub->game->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(cub->game->mlx, &cub->game->last_mouse_x, &temp);
	mlx_key_hook(cub->game->mlx, key_hook, cub);
	mlx_loop_hook(cub->game->mlx, update_player, cub);
	mlx_loop_hook(cub->game->mlx, update_npc, cub);
	mlx_loop_hook(cub->game->mlx, update_items, cub);
	mlx_loop_hook(cub->game->mlx, render_frame, cub);
}

static bool	has_cub_ext(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (false);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_cub		*cub;
	t_parsing	*parsing;

	if (argc != 2 || !has_cub_ext(argv[1]))
		error_exit(3);
	cub = ft_calloc(1, sizeof(t_cub));
	parsing = ft_calloc(1, sizeof(t_parsing));
	if (!cub || !parsing)
		exit(1);
	init_cub(argv, cub, parsing);
	if (!cub->game->mlx)
		exit(1);
	mlx_loops(cub);
	close(parsing->fd);
	mlx_loop(cub->game->mlx);
	mlx_terminate(cub->game->mlx);
	exit(0);
}
