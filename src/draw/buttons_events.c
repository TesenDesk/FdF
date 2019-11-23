/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:03:20 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:03:56 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	sooo_many_buttons(int code, t_fdf *fdf)
{
	if (code == ROTATE_Z_MINUS)
		change_rotate(fdf, 0, 0, -1);
	else if (code == ROTATE_Z_PLUS)
		change_rotate(fdf, 0, 0, 1);
	else if (code == ROTATE_Y_MINUS)
		change_rotate(fdf, 0, -1, 0);
	else if (code == ROTATE_Y_PLUS)
		change_rotate(fdf, 0, 1, 0);
	else if (code == ROTATE_X_MINUS)
		change_rotate(fdf, -1, 0, 0);
	else if (code == ROTATE_X_PLUS)
		change_rotate(fdf, 1, 0, 0);
	else if (code == ROTATE_RESET)
		change_rotate(fdf, 0, 0, 0);
	else if (code == ZOOM_RESET)
		fdf->mutation.stretch.range = DEFAULT_RANGE;
	else if (code == HUD)
		change_hud(fdf);
	else if (code == POSITION_RESET)
		reset_pos(fdf);
	else if (code == ESC)
		close_pls(NULL);
}

void	soo_many_buttons(int code, t_fdf *fdf)
{
	if (code == SCALE_RESET)
		change_stretch(fdf, 0, 0, 0);
	else if (code == ZOOM_X_PLUS)
		change_stretch(fdf, 1, 0, 0);
	else if (code == ZOOM_X_MINUS)
		change_stretch(fdf, -1, 0, 0);
	else if (code == ZOOM_Y_PLUS)
		change_stretch(fdf, 0, 1, 0);
	else if (code == ZOOM_Y_MINUS)
		change_stretch(fdf, 0, -1, 0);
	else if (code == ZOOM_Z_PLUS)
		change_stretch(fdf, 0, 0, 1);
	else if (code == ZOOM_Z_MINUS)
		change_stretch(fdf, 0, 0, -1);
	else
		sooo_many_buttons(code, fdf);
}

int		so_many_buttons(int code, void *vfdf)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)vfdf;
	if (code == UP)
		fdf->mutation.shift.y -= CHANGE_MOVE;
	else if (code == DOWN)
		fdf->mutation.shift.y += CHANGE_MOVE;
	else if (code == RIGHT)
		fdf->mutation.shift.x += CHANGE_MOVE;
	else if (code == LEFT)
		fdf->mutation.shift.x -= CHANGE_MOVE;
	else if (code == PLUS)
		change_range(fdf, 1);
	else if (code == MINUS)
		change_range(fdf, -1);
	else
		soo_many_buttons(code, fdf);
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	draw_map(fdf);
	if (fdf->draw_hud)
		draw_parameters(fdf);
	return (0);
}
