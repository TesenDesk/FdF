/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:00:16 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:01:19 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_resets(t_mlx *m, t_drawing *d)
{
	draw_button(m, d, "Backspace");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
				WHITE_COLOR, "Reset zoom");
	d->x = 190;
	draw_button(m, d, "Tab");
	mlx_string_put(m->mlx, m->win, 165, d->y + 26,
				WHITE_COLOR, "Reset rotation");
	d->x = 30;
	d->y += 70;
	draw_button(m, d, "Enter");
	mlx_string_put(m->mlx, m->win, 25, d->y + 26,
				WHITE_COLOR, "Reset position");
	d->x = 190;
	draw_button(m, d, "Num0");
	mlx_string_put(m->mlx, m->win, 185, d->y + 26,
				WHITE_COLOR, "Reset scale");
}

void	draw_control_hud_esc(t_mlx *m, t_drawing *d)
{
	draw_button(m, d, "H");
	mlx_string_put(m->mlx, m->win, d->x + 25, d->y - 6,
				WHITE_COLOR, "Show / hide HUD");
	d->x += 185;
	draw_button(m, d, "Esc");
	mlx_string_put(m->mlx, m->win, d->x + 45, d->y - 6,
				WHITE_COLOR, "Exit");
}

void	draw_controls(t_mlx *mlx)
{
	t_drawing	d;

	d.color = (int)0xA07070FF;
	d.x = 10;
	d.y = 100;
	d.h = 600;
	d.w = 300;
	draw_filled_box(mlx, &d);
	d.x = 30;
	d.y = 120;
	d.color = WHITE_COLOR;
	draw_arrows_wasd(mlx, &d);
	d.x = 30;
	d.y = 230;
	draw_qe_plus_minus(mlx, &d);
	d.y = 320;
	d.x = 30;
	draw_scales(mlx, &d);
	d.y = 510;
	d.x = 30;
	draw_resets(mlx, &d);
	d.y = 660;
	d.x = 30;
	draw_control_hud_esc(mlx, &d);
}

void	so_many_parameters(t_fdf *fdf, char *huh)
{
	void		*mlx;
	void		*win;

	mlx = fdf->mlx.mlx;
	win = fdf->mlx.win;
	mlx_string_put(mlx, win, 0, 15, WHITE_COLOR, "rotation:");
	mlx_string_put(mlx, win, 100, 15, WHITE_COLOR,
				ft_itostr(fdf->mutation.tilt.x, huh));
	mlx_string_put(mlx, win, 140, 15, WHITE_COLOR,
				ft_itostr(fdf->mutation.tilt.y, huh));
	mlx_string_put(mlx, win, 180, 15, WHITE_COLOR,
				ft_itostr(fdf->mutation.tilt.z, huh));
	mlx_string_put(mlx, win, 0, 30, WHITE_COLOR, "stretch:");
	mlx_string_put(mlx, win, 100, 30, WHITE_COLOR,
				ft_itostr(fdf->mutation.stretch.x, huh));
	mlx_string_put(mlx, win, 140, 30, WHITE_COLOR,
				ft_itostr(fdf->mutation.stretch.y, huh));
	mlx_string_put(mlx, win, 180, 30, WHITE_COLOR,
				ft_itostr(fdf->mutation.stretch.z, huh));
}

void	draw_parameters(t_fdf *fdf)
{
	char		huh[12];
	void		*mlx;
	void		*win;

	mlx = fdf->mlx.mlx;
	win = fdf->mlx.win;
	mlx_string_put(mlx, win, 0, 0, WHITE_COLOR, "position:");
	mlx_string_put(mlx, win, 100, 0, WHITE_COLOR,
				ft_itostr(fdf->mutation.shift.x, huh));
	mlx_string_put(mlx, win, 140, 0, WHITE_COLOR,
				ft_itostr(fdf->mutation.shift.y, huh));
	so_many_parameters(fdf, huh);
	mlx_string_put(mlx, win, 180, 0, WHITE_COLOR, "range:");
	draw_bar(&fdf->mlx, fdf->mutation.stretch.range, 10, 7 * 1600 + 275);
	mlx_string_put(mlx, win, 240, 0, WHITE_COLOR,
				ft_itostr(fdf->mutation.stretch.range, huh));
	draw_controls(&fdf->mlx);
}
