/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:24:17 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:25:45 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line_between(t_fdf *fdf, t_wire *w)
{
	int			e;
	int			ee;
	int			x;
	int			y;

	w->dy *= -1;
	x = w->from.x;
	y = w->from.y;
	e = w->dx + w->dy;
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, w->to.x, w->to.y, w->color);
	while (x != w->to.x || y != w->to.y)
	{
		mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, x, y, w->color);
		ee = e * 2;
		if (ee >= w->dy)
		{
			x += w->sign_x;
			e += w->dy;
		}
		if (ee <= w->dx)
		{
			y += w->sign_y;
			e += w->dx;
		}
	}
}

void	draw_connection_if_necessary(t_fdf *fdf, t_wire *w)
{
	if (need_to_draw_this(w))
	{
		w->dx = abs(w->to.x - w->from.x);
		w->dy = abs(w->to.y - w->from.y);
		w->sign_x = w->from.x > w->to.x ? -1 : 1;
		w->sign_y = w->from.y > w->to.y ? -1 : 1;
		draw_line_between(fdf, w);
	}
}
