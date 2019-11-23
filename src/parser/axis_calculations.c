/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axis_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 05:31:21 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 05:36:22 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				set_the_largest_abscissa(t_fdf *fdf)
{
	fdf->map.width = fdf->map.bit_map.total;
	return ;
}

void				set_the_largest_ordinate(t_fdf *fdf)
{
	fdf->map.height = fdf->map.bit_map.total / fdf->map.width;
	return ;
}

void				set_the_abscissa_counter(int *x_counter, t_fdf *fdf)
{
	*x_counter = fdf->map.width;
	return ;
}

void				count_applicate(t_fdf *fdf)
{
	fdf->map.length = (fdf->reader.z_max - fdf->reader.z_min);
	return ;
}
