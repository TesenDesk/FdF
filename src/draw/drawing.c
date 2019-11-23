/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:20:55 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 03:54:54 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		close_pls(void *param)
{
	(void)param;
	exit(0);
}

void	rotate_x(t_cordcase *c, long double x_rad, long double y_rad,
															long double z_rad)
{
	long		x;
	long		y;
	long		z;

	y = (c->y * (long)(cosl(x_rad) * MULTIPLIER) -
			c->z * (long)(sinl(x_rad) * MULTIPLIER)) / MULTIPLIER;
	z = (c->y * (long)(sinl(x_rad) * MULTIPLIER) +
			c->z * (long)(cosl(x_rad) * MULTIPLIER)) / MULTIPLIER;
	c->y = (int)y;
	c->z = (int)z;
	x = (c->x * (long)(cosl(y_rad) * MULTIPLIER) +
			c->z * (long)(sinl(y_rad) * MULTIPLIER)) / MULTIPLIER;
	c->x = (int)x;
	x = (c->x * (long)(cosl(z_rad) * MULTIPLIER) -
			c->y * (long)(sinl(z_rad) * MULTIPLIER)) / MULTIPLIER;
	y = (c->x * (long)(sinl(z_rad) * MULTIPLIER) +
			c->y * (long)(cosl(z_rad) * MULTIPLIER)) / MULTIPLIER;
	c->x = (int)x;
	c->y = (int)y;
}

void	perform_rotation(t_fdf *fdf, int i, t_cordcase *ret)
{
	t_remake	r;

	ret->x = i % fdf->map.width;
	ret->y = i / fdf->map.width;
	r.pixel_as_ptr = fdf->map.bit_map.items[i];
	ret->z = r.pixel.z;
	ret->x *= fdf->mutation.stretch.x;
	ret->y *= fdf->mutation.stretch.y;
	ret->z = ret->z * fdf->mutation.stretch.z / 2;
	ret->x -= (fdf->map.width - 1) * fdf->mutation.stretch.x / 2;
	ret->y -= (fdf->map.height - 1) * fdf->mutation.stretch.y / 2;
	rotate_x(ret, fdf->mutation.tilt.x * PI / 180,
			fdf->mutation.tilt.y * PI / 180,
			fdf->mutation.tilt.z * PI / 180);
	ret->x = (ret->x * fdf->mutation.stretch.range) / 100;
	ret->y = (ret->y * fdf->mutation.stretch.range) / 100;
	ret->x += fdf->mutation.shift.x;
	ret->y += fdf->mutation.shift.y;
}

void	draw_box(t_mlx *mlx, int w, int h, int where)
{
	int			x;
	int			y;
	int			i;

	x = where % SCREEN_WIDTH;
	y = where / SCREEN_WIDTH;
	i = w;
	while (--i)
		mlx_pixel_put(mlx->mlx, mlx->win, x++, y, WHITE_COLOR);
	i = h;
	while (--i)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y++, WHITE_COLOR);
	i = w;
	while (--i)
		mlx_pixel_put(mlx->mlx, mlx->win, x--, y, WHITE_COLOR);
	i = h;
	while (--i)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y--, WHITE_COLOR);
}

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

int		need_to_draw_this(t_wire *w)
{
	if ((w->from.x >= 0 && w->from.x < SCREEN_WIDTH &&
			w->from.y >= 0 && w->from.y < SCREEN_HEIGHT) ||
			(w->to.x >= 0 && w->to.x < SCREEN_WIDTH &&
			w->to.y >= 0 && w->to.y < SCREEN_HEIGHT))
		return (1);
	return (0);
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

void	draw_map(t_fdf *fdf)
{
	t_wire		w;
	int			i;

	i = -1;
	while (++i < fdf->map.size)
		draw_connections_to_neighbours(fdf, &w, i);
}

void	change_range(t_fdf *fdf, int mode)
{
	int			*range;

	range = &fdf->mutation.stretch.range;
	if (!mode)
		*range = DEFAULT_RANGE;
	else
	{
		*range += CHANGE_RANGE * mode;
		if (*range > MAX_RANGE)
			*range = MAX_RANGE;
		else if (*range < MIN_RANGE)
			*range = MIN_RANGE;
	}
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

void	draw_button(t_mlx *mlx, t_drawing *d, char *name)
{
	int			leng;

	leng = ft_strlen(name);
	draw_box(mlx, 10 + (10 * leng), 20,
			(d->y - 5) * SCREEN_WIDTH + d->x - 5);
	mlx_string_put(mlx->mlx, mlx->win, d->x, d->y - 7, YELLOW_COLOR, name);
}

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

int		early_mlx_init(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, SCREEN_TITLE);
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 0, 0x00FFFF00,
			"Mlx initializing complete!");
	reset_pos(fdf);
	change_stretch(fdf, 0, 0, 0);
	fdf->mutation.stretch.range = DEFAULT_RANGE;
	change_rotate(fdf, 0, 0, 0);
	fdf->map.size = fdf->map.height * fdf->map.width;
	fdf->draw_hud = 1;
	draw_map(fdf);
	draw_controls(&fdf->mlx);
	mlx_hook(fdf->mlx.win, 2, 1UL << 0UL, so_many_buttons, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_pls, NULL);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}
