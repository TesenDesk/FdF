/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_coords.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjerde <jjerde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 04:05:41 by jjerde            #+#    #+#             */
/*   Updated: 2019/11/23 04:25:49 by jjerde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_default_zoom(t_fdf *fdf)
{
	t_cordcase	c;
	int			max_x;
	int			max_y;
	double		k;

	perform_rotation(fdf, 0, &c);
	max_x = SCREEN_WIDTH / 2 - c.x;
	max_y = SCREEN_HEIGHT / 2 - c.y;
	if (max_y < max_x)
		k = 0.95 / ((double)max_x * 2 / SCREEN_WIDTH);
	else
		k = 0.95 / ((double)max_y * 2 / SCREEN_HEIGHT);
	fdf->default_range = (int)(DEFAULT_RANGE * k);
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
