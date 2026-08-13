/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 13:40:00 by alegeber          #+#    #+#             */
/*   Updated: 2026/08/13 14:58:10 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Darkens the frozen frame in place. The loop hooks stop writing to the
// image while paused, so the dimmed frame simply stays on screen until
// the game resumes and render_frame overwrites every pixel again.
static void	dim_frame(mlx_image_t *img)
{
	uint8_t	*px;
	int		i;
	int		total;

	px = img->pixels;
	total = (int)(img->width * img->height) * 4;
	i = 0;
	while (i < total)
	{
		px[i] /= PAUSE_DIM;
		px[i + 1] /= PAUSE_DIM;
		px[i + 2] /= PAUSE_DIM;
		i += 4;
	}
}

// Fills one rectangle, skipping anything that falls outside the frame.
static void	draw_rect(mlx_image_t *img, t_point start, t_point size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (start.x + x >= 0 && start.x + x < (int)img->width
				&& start.y + y >= 0 && start.y + y < (int)img->height)
				mlx_put_pixel(img, start.x + x, start.y + y, WHITE);
			x++;
		}
		y++;
	}
}

// Dims the frame and stamps the two pause bars in its centre, once per
// pause so the work is not repeated every frame while frozen.
void	draw_pause_overlay(t_cub *cub)
{
	mlx_image_t	*img;
	t_point		size;
	int			cx;
	int			cy;

	img = cub->game->img;
	if (!img || cub->pause_drawn)
		return ;
	dim_frame(img);
	cx = (int)img->width / 2;
	cy = (int)img->height / 2 - PAUSE_BAR_H / 2;
	size = (t_point){PAUSE_BAR_W, PAUSE_BAR_H};
	draw_rect(img, (t_point){cx - PAUSE_BAR_GAP / 2 - PAUSE_BAR_W, cy}, size);
	draw_rect(img, (t_point){cx + PAUSE_BAR_GAP / 2, cy}, size);
	cub->pause_drawn = true;
}

// Flips the pause state: pausing releases the cursor so the player can
// click the window's X button, resuming re-captures it and re-syncs the
// mouselook anchor so the view does not snap to wherever the cursor was
// left. Ignored once the win/lose screen is up.
void	toggle_pause(t_cub *cub)
{
	int32_t	temp;

	if (cub->game_over || cub->you_win)
		return ;
	cub->paused = !cub->paused;
	if (cub->paused)
	{
		cub->pause_drawn = false;
		mlx_set_cursor_mode(cub->game->mlx, MLX_MOUSE_NORMAL);
	}
	else
	{
		mlx_set_cursor_mode(cub->game->mlx, MLX_MOUSE_DISABLED);
		mlx_get_mouse_pos(cub->game->mlx, &cub->game->last_mouse_x, &temp);
	}
}

// Key hook: TAB toggles the pause on the press edge only, so holding the
// key down does not flicker the game in and out of the paused state.
void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
		toggle_pause((t_cub *)param);
}
