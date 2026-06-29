/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:11:03 by alegeber          #+#    #+#             */
/*   Updated: 2026/06/24 15:41:59 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

static void	move_player(t_cub *cub, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = cub->player->pos_x + move_x;
	new_y = cub->player->pos_y + move_y;
	if (!is_wall(cub->map, (int)new_x, (int)cub->player->pos_y))
		cub->player->pos_x = new_x;
	if (!is_wall(cub->map, (int)cub->player->pos_x, (int)new_y))
		cub->player->pos_y = new_y;
}

void	update_player(void *param)
{
	t_cub	*cub;
	double	move_speed;
	double	rot_speed;
	double	move_x;
	double	move_y;

	cub = (t_cub *)param;
	move_speed = 0.05;
	rot_speed = 0.03;
	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_W))
	{
		move_x += cub->player->dir_x * move_speed;
		move_y += cub->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_S))
	{
		move_x -= cub->player->dir_x * move_speed;
		move_y -= cub->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_A))
	{
		move_x += cub->player->dir_y * move_speed;
		move_y -= cub->player->dir_x * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_D))
	{
		move_x -= cub->player->dir_y * move_speed;
		move_y += cub->player->dir_x * move_speed;
	}
	if (move_x != 0 || move_y != 0)
		move_player(cub, move_x, move_y);
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_LEFT))
		rotate_player(cub->player, -rot_speed);
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_RIGHT))
		rotate_player(cub->player, rot_speed);
}

