/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   police.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 18:59:12 by MP9               #+#    #+#             */
/*   Updated: 2026/08/12 16:28:39 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Move our npc towards the next target in its path,
// checking if it's reached the target.
void	update_npc(void *param)
{
	t_cub	*cub;
	t_npc	*npc;
	t_bfs	bfs;

	cub = (t_cub *)param;
	npc = cub->npc;
	if (!npc || !npc->active || cub->game_over || cub->you_win)
		return ;
	ft_memset(&bfs, 0, sizeof(t_bfs));
	bfs.now = get_time();
	get_length(cub, npc, &bfs, bfs.now);
	if (cub->npc->path_length < 2)
		return ;
	if (cub->npc->current_target >= cub->npc->path_length)
		return ;
	get_distance(cub, npc, &bfs);
	if (bfs.dist < 0.05)
	{
		cub->npc->current_target++;
		return ;
	}
	move_n_get_distance(cub, npc, &bfs);
	if (bfs.dist < NPC_CATCH_DIST)
		cub->game_over = true;
}

// draws our npc on the minimap, calculating its position relative to
// the player and ensuring it is within the minimap's bounds.
void	draw_npc(mlx_image_t *img, t_cub *cub)
{
	if (!cub->npc || !cub->npc->active)
		return ;
	cub->npc->offset_x = (int)((cub->npc->pos_x - cub->player->pos_x)
			* MINIMAP_TILE);
	cub->npc->offset_y = (int)((cub->npc->pos_y - cub->player->pos_y)
			* MINIMAP_TILE);
	if (cub->npc->offset_x < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_x > MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_y < -MINIMAP_RADIUS * MINIMAP_TILE
		|| cub->npc->offset_y > MINIMAP_RADIUS * MINIMAP_TILE)
		return ;
	cub->npc->view = (2 * MINIMAP_RADIUS + 1) * MINIMAP_TILE;
	cub->npc->minimap_x = WIDTH - MINIMAP_PADDING - cub->npc->view;
	cub->npc->minimap_y = MINIMAP_PADDING;
	cub->npc->screen_x = cub->npc->minimap_x + MINIMAP_RADIUS * MINIMAP_TILE
		+ MINIMAP_TILE / 2 + cub->npc->offset_x;
	cub->npc->screen_y = cub->npc->minimap_y + MINIMAP_RADIUS * MINIMAP_TILE
		+ MINIMAP_TILE / 2 + cub->npc->offset_y;
	cub->npc->ps = MINIMAP_TILE / 3;
	if (cub->npc->ps < 3)
		cub->npc->ps = 3;
	draw_tile(img, (t_point){cub->npc->screen_x - cub->npc->ps / 2,
		cub->npc->screen_y - cub->npc->ps / 2}, cub->npc->ps, BLUE);
}

// draw the npc as a police sprite in the 3D world, using its position 
// and the raycaster buffer to ensure correct rendering order and occlusion.
void	draw_sprite(t_cub *cub, double *raycaster_buffer)
{
	t_dpoint	pos;

	if (!cub->npc || !cub->npc->active)
		return ;
	pos.x = cub->npc->pos_x;
	pos.y = cub->npc->pos_y;
	draw_billboard_sprite(cub, pos, cub->textures->police_tex,
		raycaster_buffer);
}
