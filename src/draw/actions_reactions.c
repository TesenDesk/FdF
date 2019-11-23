/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_reactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:04:33 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:04:44 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_range(t_fdf *fdf, int mode)
{
	int			*range;

	range = &fdf->mutation.stretch.range;
	if (!mode)
		*range = fdf->default_range;
	*range += CHANGE_RANGE * mode;
	if (*range > MAX_RANGE)
		*range = MAX_RANGE;
	else if (*range < MIN_RANGE)
		*range = MIN_RANGE;
}

void	change_stretch(t_fdf *fdf, int x_mode, int y_mode, int z_mode)
{
	int			tmp;

	if (!x_mode && !y_mode && !z_mode)
	{
		fdf->mutation.stretch.x = DEFAULT_STRETH;
		fdf->mutation.stretch.y = DEFAULT_STRETH;
		fdf->mutation.stretch.z = DEFAULT_STRETH / 2;
		return ;
	}
	if ((tmp = fdf->mutation.stretch.x + CHANGE_STRETCH * x_mode) > 0)
		fdf->mutation.stretch.x = tmp;
	if ((tmp = fdf->mutation.stretch.y + CHANGE_STRETCH * y_mode) > 0)
		fdf->mutation.stretch.y = tmp;
	if ((tmp = fdf->mutation.stretch.z + CHANGE_STRETCH * z_mode) >= 0)
		fdf->mutation.stretch.z = tmp;
}

void	change_rotate(t_fdf *fdf, int x_mode, int y_mode, int z_mode)
{
	t_tilt		*tilt;

	tilt = &fdf->mutation.tilt;
	if (!x_mode && !y_mode && !z_mode)
	{
		tilt->x = DEFAULT_ROT_X;
		tilt->y = DEFAULT_ROT_Y;
		tilt->z = DEFAULT_ROT_Z;
		return ;
	}
	tilt->x += CHANGE_ROTATE * x_mode;
	tilt->y += CHANGE_ROTATE * y_mode;
	tilt->z += CHANGE_ROTATE * z_mode;
	if (tilt->x >= MAX_ROTATE)
		tilt->x -= MAX_ROTATE;
	else if (tilt->x < MIN_ROTATE)
		tilt->x += MAX_ROTATE;
	if (tilt->y >= MAX_ROTATE)
		tilt->y -= MAX_ROTATE;
	else if (tilt->y < MIN_ROTATE)
		tilt->y += MAX_ROTATE;
	if (tilt->z >= MAX_ROTATE)
		tilt->z -= MAX_ROTATE;
	else if (tilt->z < MIN_ROTATE)
		tilt->z += MAX_ROTATE;
}

void	change_hud(t_fdf *fdf)
{
	if (fdf->draw_hud)
		fdf->draw_hud = 0;
	else
		fdf->draw_hud = 1;
}

void	reset_pos(t_fdf *fdf)
{
	fdf->mutation.shift.x = DEFAULT_POS_X;
	fdf->mutation.shift.y = DEFAULT_POS_Y;
}
