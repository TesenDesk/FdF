/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:09:03 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/22 23:57:22 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
**---------------------------------INCLUDES-------------------------------------
*/

# include <math.h>
# include "libft.h"
# include "mlx.h"

/*
**---------------------------------MACROSES-------------------------------------
*/

# define DEBUG_MODE		1
# define PI				3.14159265359
# define MAX_ROTATE		360
# define MIN_ROTATE		0
# define MAX_RANGE		200
# define MIN_RANGE		1
# define DEFAULT_STRETH	100
# define DEFAULT_ROT_X	60
# define DEFAULT_ROT_Y	40
# define DEFAULT_ROT_Z	0
# define DEFAULT_RANGE	50
# define DEFAULT_POS_X	800
# define DEFAULT_POS_Y	600
# define DEFAULT_COLOR	0x0032A852
# define WHITE_COLOR	0x00FFFFFF
# define BROWN_COLOR	0x00CD853F
# define BLUE_COLOR		0x000000FF
# define GREEN_COLOR	0x0000FF00
# define YELLOW_COLOR	0x00FFFF00
# define SCREEN_WIDTH	1600
# define SCREEN_HEIGHT	1200
# define MULTIPLIER		100000
# define SCREEN_TITLE	"/Users/Admin/Applications/.secret/42prj/fdf/fdf.out"

typedef enum			e_elevations
{
	HADOPELAGIC_COLOR = 0x000237,
	ABYSSALOPELAGIC_1_COLOR = 0x000876,
	ABYSSALOPELAGIC_2_COLOR = 0x0019d2,
	BATHYPELAGIC_COLOR = 0x2c6cf6,
	MESOPELAGIC_COLOR = 0x60ccfa0,
	PLAIN = 0x78fbfd0,
	HIGHLAND = 0x326e3a0,
	PLATEAUS = 0xa8d78c,
	LOW_MOUNTAIN = 0xccac370,
	MEDIUM_MOUNTAIN = 0x9c7c0b0,
	HIGH_MOUNTAIN = 0x4608730,
	HIGHEST_MOUNTAIN = 0xd4ced9
}						t_elevations;

# define CHANGE_MOVE	10
# define CHANGE_ROTATE	10
# define CHANGE_STRETCH	1
# define CHANGE_RANGE	2

typedef enum			e_buttons
{
	ZOOM_X_PLUS = 30,
	ZOOM_X_MINUS = 33,
	ZOOM_Y_PLUS = 47,
	ZOOM_Y_MINUS = 43,
	ZOOM_Z_PLUS = 39,
	ZOOM_Z_MINUS = 41,
	ROTATE_X_MINUS = 1,
	ROTATE_X_PLUS = 13,
	ROTATE_Y_MINUS = 0,
	ROTATE_Y_PLUS = 2,
	ROTATE_Z_PLUS = 14,
	ROTATE_Z_MINUS = 12,
	ROTATE_RESET = 10,
	PLUS = 24,
	MINUS = 27,
	ZOOM_RESET = 51,
	LEFT = 123,
	RIGHT,
	DOWN,
	UP,
	ESC = 53
}						t_buttons;

/*
**---------------------------------READER---------------------------------------
*/

typedef struct			s_drawing
{
	int					x;
	int					y;
	int					color;
	int					w;
	int					h;
}						t_drawing;

typedef struct			s_cordcase
{
	int					x;
	int					y;
}						t_cordcase;

typedef struct			s_wire
{
	t_cordcase			from;
	t_cordcase			to;
	int					dx;
	int					dy;
	int					sign_x;
	int					sign_y;
	int					color;
}						t_wire;


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
}						t_pixel;

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
	int					size;
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
	int					range;
}						t_stretch;

typedef struct			s_shift
{
	int					x;
	int					y;
	int					z;
}						t_shift;

typedef struct			s_tilt
{
	int					x;
	int					y;
	int					z;
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
	void				*win;
}						t_mlx;

typedef struct			s_fdf
{
	t_read				reader;
	t_map				map;
	t_mutation			mutation;
	t_mlx				mlx;
	char				graphical_state;
}						t_fdf;

/*
**---------------------------FUNCTION_DECLARATIONS------------------------------
*/

int						validate_read_and_parse(int argc, char **argv,
							t_fdf *fdf);

#endif
