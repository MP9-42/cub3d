/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 10:11:03 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/12 16:00:36 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// allows player to move with camera movement
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

// checks if there is a wall in the direction the player 
// is moving and updates the player's position accordingly
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

// moves the player accordingly to the input received from the user.
static void	get_move_input(t_cub *cub, double *move_x, double *move_y)
{
	double	move_speed;

	move_speed = 0.05;
	*move_x = 0;
	*move_y = 0;
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_W))
	{
		*move_x += cub->player->dir_x * move_speed;
		*move_y += cub->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_S))
	{
		*move_x -= cub->player->dir_x * move_speed;
		*move_y -= cub->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_A))
	{
		*move_x += cub->player->dir_y * move_speed;
		*move_y -= cub->player->dir_x * move_speed;
	}
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_D))
	{
		*move_x -= cub->player->dir_y * move_speed;
		*move_y += cub->player->dir_x * move_speed;
	}
}

// handles camera movement based on the user input
static void	handle_rotation(t_cub *cub, double rot_speed)
{
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_LEFT))
		rotate_player(cub->player, -rot_speed);
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_RIGHT))
		rotate_player(cub->player, rot_speed);
}

// accept movement input from the user and update the player's
// position and camera direction accordingly
void	update_player(void *param)
{
	t_cub	*cub;
	double	move_x;
	double	move_y;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(cub->game->mlx);
		exit(0);
	}
	if (cub->game_over || cub->you_win)
		return ;
	get_move_input(cub, &move_x, &move_y);
	if (move_x != 0 || move_y != 0)
		move_player(cub, move_x, move_y);
	handle_rotation(cub, 0.03);
}
