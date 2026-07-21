/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 15:37:17 by MP9               #+#    #+#             */
/*   Updated: 2026/07/21 17:04:40 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_t	*init_window(t_cub *cub)
{
	mlx_t		*mlx;

	cub->game->width = WIDTH;
	cub->game->height = HEIGHT;
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!mlx)
		return (NULL);
	cub->game->mlx = mlx;
	cub->game->player = cub->player;
	cub->game->cub = cub;
	get_image(cub->game, cub);
	mlx_loop_hook(mlx, render_frame, cub);
	mlx_loop(mlx);
	return (mlx);
}

void	get_image(t_game *game, t_cub *cub)
{
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return ;
	render_map(game->img, cub);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_resize_hook(game->mlx, resize_hook, game);
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;

	game = param;
	game->width = width;
	game->height = height;
}

void	redraw(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	if (!game->img)
		return ;
	render_map(game->img, game->cub);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
}
