/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:09:03 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/12 21:56:42 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"

typedef struct			s_read
{
	int					fd;
	t_vector			lines;
	int					x_max;
	int					z_min;
	int					z_max;
	int					is_color;
}						t_read;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}                       t_point;

typedef struct          s_fdf
{
	t_read				reader;
}                       t_fdf;

int						validate_read_and_parse(int argc, char **argv,
							t_fdf *fdf)

#endif