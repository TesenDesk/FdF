/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:09:03 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/15 22:54:18 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
**---------------------------------INCLUDES-------------------------------------
*/

#include <math.h>
#include "libft.h"

/*
**---------------------------------MACROSES-------------------------------------
*/

# define DEFAULT_COLOR	0x0032A852
# define SCREEN_WIDTH	1600
# define SCREEN_HEIGHT	1200
# define SCREEN_TITLE	"????????????"


/*
**---------------------------------READER---------------------------------------
*/

typedef struct			s_read
{
	int					fd;
	t_vector			lines;
	int					read_state;
	int					z_min;
	int					z_max;
}						t_read;

/*
**------------------------------------MAP---------------------------------------
*/

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

/*
**---------------------------------MUTATION-------------------------------------
*/

typedef struct			s_stretch
{
	int					x;
	int					y;
	int					z;
}						t_stretch;

typedef struct			s_shift
{
	int					x;
	int					y;
	int					z;
}						t_shift;

typedef struct			s_tilt
{
	double				x;
	double				y;
	double				z;
}						t_tilt;

typedef struct			s_position
{
	int					x;
	int					y;
	int					z;
}						t_position;

typedef struct			s_mutation
{
	t_stretch			stretch;
	t_shift				shift;
	t_tilt				tilt;
	t_position			position;
}						t_mutation;

/*
**-------------------------------------FDF--------------------------------------
*/

typedef struct			s_mlx
{
	void				*mlx;
	void 				*win;
}						t_mlx;

typedef struct          s_fdf
{
	t_read				reader;
	t_map				map;
	t_mutation			mutation;
	t_mlx				mlx;
}                       t_fdf;

/*
**---------------------------FUNCTION_DECLARATIONS------------------------------
*/

int						validate_read_and_parse(int argc, char **argv,
							t_fdf *fdf);

#endif