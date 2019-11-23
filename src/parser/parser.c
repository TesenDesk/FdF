/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:22:32 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 06:50:38 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				move_top_to_the_beginning_of_the_read_line(char *line,
						char **top)
{
	*top = line;
	return ;
}

void				record_applicate_extremes(t_fdf *fdf)
{
	static int		is_set;
	t_vector		*v;
	t_remake		r;

	v = &fdf->map.bit_map;
	r.pixel_as_ptr = v->items[v->total - 1];
	if (!is_set)
	{
		fdf->reader.z_max = r.pixel.z;
		fdf->reader.z_min = r.pixel.z;
		is_set = TRUE;
	}
	else
	{
		if (r.pixel.z < fdf->reader.z_min)
			fdf->reader.z_min = r.pixel.z;
		else if (r.pixel.z > fdf->reader.z_max)
			fdf->reader.z_max = r.pixel.z;
	}
	return ;
}

int					parse_applicate(char **top, t_pixel *pixel)
{
	char			*tip;
	intmax_t		z;

	if (**top)
	{
		if (ft_str_to_intmax(*top, &tip, 10, &z) || *top == tip)
			return (FAILURE);
			*top = tip;
			pixel->z = (int)z;
	}
	return (SUCCESS);
}
