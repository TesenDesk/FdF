/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:09:03 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/14 16:09:44 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"

# define DEFAULT_COLOR	0x0032A852

typedef struct			s_read
{
	int					fd;
	t_vector			lines;
	int					read_state;
	int					z_min;
	int					z_max;
}						t_read;

typedef struct			s_pixel
{
	int					z : sizeof(int) * BITS_AT_BYTE;
	int					color : sizeof(int) * BITS_AT_BYTE;
}                       t_pixel;

typedef union			u_remake
{
	t_pixel				pixel;
	void				*pixel_as_ptr;
}						t_remake;

typedef struct			s_map
{
	t_vector			bit_map;
	int					width;
	int					height;
	int					length;
	int					bits_per_pixel;
}						t_map;

typedef struct          s_fdf
{
	t_read				reader;
	t_map				map;
}                       t_fdf;

int						validate_read_and_parse(int argc, char **argv,
							t_fdf *fdf);

#endif