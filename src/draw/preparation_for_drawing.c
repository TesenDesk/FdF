/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation_for_drawing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:13:09 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:25:34 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		need_to_draw_this(t_wire *w)
{
	if ((w->from.x >= 0 && w->from.x < SCREEN_WIDTH &&
			w->from.y >= 0 && w->from.y < SCREEN_HEIGHT) ||
			(w->to.x >= 0 && w->to.x < SCREEN_WIDTH &&
			w->to.y >= 0 && w->to.y < SCREEN_HEIGHT))
		return (1);
	return (0);
}

void	draw_down(t_fdf *fdf, t_wire *w, int pos)
{
	int			target;

	target = pos + fdf->map.width;
	if (target / fdf->map.width < fdf->map.height)
	{
		perform_rotation(fdf, target, &w->to);
		draw_connection_if_necessary(fdf, w);
	}
}

void	draw_left(t_fdf *fdf, t_wire *w, int pos)
{
	int			target;

	target = pos + 1;
	if (target / fdf->map.width <= fdf->map.height && target % fdf->map.width)
	{
		perform_rotation(fdf, target, &w->to);
		draw_connection_if_necessary(fdf, w);
	}
}

void	draw_connections_to_neighbours(t_fdf *fdf, t_wire *w, int pos)
{
	t_remake	r;

	if (!(pos % fdf->map.width))
		perform_rotation(fdf, pos, &w->from);
	else
		w->from = w->to;
	r.pixel_as_ptr = fdf->map.bit_map.items[pos];
	w->color = r.pixel.color;
	draw_down(fdf, w, pos);
	draw_left(fdf, w, pos);
}
