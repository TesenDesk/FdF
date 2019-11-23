/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_color_characteristics.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 05:26:43 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 05:27:27 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					has_color_characteristic(char c)
{
	return (c == ',');
}

void				set_default_color(t_pixel *pixel)
{
	if (pixel->z <= -800)
		pixel->color = HADOPELAGIC_COLOR;
	else if (pixel->z <= -600)
		pixel->color = ABYSSALOPELAGIC_1_COLOR;
	else if (pixel->z <= -400)
		pixel->color = ABYSSALOPELAGIC_2_COLOR;
	else if (pixel->z <= -200)
		pixel->color = BATHYPELAGIC_COLOR;
	else if (pixel->z <= 0)
		pixel->color = MESOPELAGIC_COLOR;
	else if (pixel->z <= 20)
		pixel->color = PLAIN;
	else if (pixel->z <= 50)
		pixel->color = HIGHLAND;
	else if (pixel->z <= 100)
		pixel->color = PLATEAUS;
	else if (pixel->z <= 200)
		pixel->color = LOW_MOUNTAIN;
	else if (pixel->z <= 400)
		pixel->color = MEDIUM_MOUNTAIN;
	else if (pixel->z <= 600)
		pixel->color = HIGH_MOUNTAIN;
	else
		pixel->color = HIGHEST_MOUNTAIN;
	return ;
}

int					convert_string_to_color_number(char **top, t_pixel *pixel)
{
	char			*str;
	char			*end;
	uintmax_t		color;

	str = *top;
	++str;
	end = NULL;
	if (ft_str_to_uintmax(str, &end, 16, &color))
		return (FAILURE);
	pixel->color = (int)color;
	*top = end;
	return (SUCCESS);
}

int					enter_application_and_color_data(t_fdf *fdf,
						void *pixel_as_ptr)
{
	t_vector		*v;

	v = &fdf->map.bit_map;
	if (ft_vector_add(v, pixel_as_ptr))
		return (FAILURE);
	return (SUCCESS);
}
