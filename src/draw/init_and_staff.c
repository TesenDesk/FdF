/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_staff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:20:55 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:25:30 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		close_pls(void *param)
{
	(void)param;
	exit(0);
}

void	draw_button(t_mlx *mlx, t_drawing *d, char *name)
{
	int			leng;

	leng = ft_strlen(name);
	draw_box(mlx, 10 + (10 * leng), 20,
			 (d->y - 5) * SCREEN_WIDTH + d->x - 5);
	mlx_string_put(mlx->mlx, mlx->win, d->x, d->y - 7, YELLOW_COLOR, name);
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

void	draw_map(t_fdf *fdf)
{
	t_wire		w;
	int			i;

	i = -1;
	while (++i < fdf->map.size)
		draw_connections_to_neighbours(fdf, &w, i);
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
	change_rotate(fdf, 0, 0, 0);
	fdf->map.size = fdf->map.height * fdf->map.width;
	fdf->draw_hud = 1;
	calculate_default_zoom(fdf);
	change_range(fdf, 0);
	draw_map(fdf);
	draw_controls(&fdf->mlx);
	mlx_hook(fdf->mlx.win, 2, 1UL << 0UL, so_many_buttons, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_pls, NULL);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}
