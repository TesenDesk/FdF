/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_advanced.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:02:07 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:25:36 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_filled_box(t_mlx *mlx, t_drawing *d)
{
	int			i;
	int			k;

	k = -1;
	while (++k < d->h)
	{
		i = -1;
		while (++i < d->w)
			mlx_pixel_put(mlx->mlx, mlx->win, d->x + i, d->y + k, d->color);
	}
}

void	draw_bar(t_mlx *mlx, int w, int h, int where)
{
	int			i;
	int			k;
	int			x;
	int			y;

	draw_box(mlx, MAX_RANGE + 4, h + 4, where - 2 - SCREEN_WIDTH * 2);
	x = where % SCREEN_WIDTH;
	y = where / SCREEN_WIDTH;
	k = -1;
	while (++k < h)
	{
		i = -1;
		while (++i < w)
			mlx_pixel_put(mlx->mlx, mlx->win, i + x, k + y, YELLOW_COLOR);
	}
}

void	draw_arrows_wasd(t_mlx *m, t_drawing *d)
{
	d->y += 23;
	draw_button(m, d, "<");
	d->x += 23;
	draw_button(m, d, "v");
	d->y -= 23;
	draw_button(m, d, "^");
	d->x += 23;
	d->y += 23;
	draw_button(m, d, ">");
	mlx_string_put(m->mlx, m->win, 25, d->y + 36,
			WHITE_COLOR, "Move map");
	d->x = 190;
	d->y = 143;
	draw_button(m, d, "A");
	d->x += 23;
	draw_button(m, d, "S");
	d->y -= 23;
	draw_button(m, d, "W");
	d->x += 23;
	d->y += 23;
	draw_button(m, d, "D");
	mlx_string_put(m->mlx, m->win, 145, d->y + 26,
				WHITE_COLOR, "Change x / y");
	mlx_string_put(m->mlx, m->win, 145, d->y + 41,
				WHITE_COLOR, "axis rotation");
}

void	draw_qe_plus_minus(t_mlx *m, t_drawing *d)
{
	draw_button(m, d, "Q");
	d->x += 53;
	draw_button(m, d, "E");
	mlx_string_put(m->mlx, m->win, d->x - 25, d->y - 7,
				WHITE_COLOR, "/");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
				WHITE_COLOR, "Change z");
	mlx_string_put(m->mlx, m->win, 15, d->y + 41,
				WHITE_COLOR, "axis rotation");
	d->x = 190;
	draw_button(m, d, "+");
	d->x += 53;
	draw_button(m, d, "-");
	mlx_string_put(m->mlx, m->win, d->x - 25, d->y - 7,
				WHITE_COLOR, "/");
	mlx_string_put(m->mlx, m->win, 175, d->y + 26,
				WHITE_COLOR, "Change zoom");
	mlx_string_put(m->mlx, m->win, 195, d->y + 41,
				WHITE_COLOR, "(range)");
}

void	draw_scales(t_mlx *m, t_drawing *d)
{
	draw_button(m, d, "Num7");
	d->x += 83;
	draw_button(m, d, "Num9");
	mlx_string_put(m->mlx, m->win, d->x - 25, d->y - 7,
			WHITE_COLOR, "/");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
			WHITE_COLOR, "Change x-axis scale");
	d->y += 60;
	d->x = 30;
	draw_button(m, d, "Num4");
	d->x += 83;
	draw_button(m, d, "Num6");
	mlx_string_put(m->mlx, m->win, d->x - 25, d->y - 7,
			WHITE_COLOR, "/");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
			WHITE_COLOR, "Change x-axis scale");
	d->y += 60;
	d->x = 30;
	draw_button(m, d, "Num1");
	d->x += 83;
	draw_button(m, d, "Num3");
	mlx_string_put(m->mlx, m->win, d->x - 25, d->y - 7,
			WHITE_COLOR, "/");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
			WHITE_COLOR, "Change z-axis scale");
}
