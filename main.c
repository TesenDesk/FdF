#include "mlx.h"

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

#define X_AXIS	0
#define Y_AXIS	1
#define Z_AXIS	2
#define ROT_L	0
#define ROT_R	1

typedef struct s_params
{
		int color;
		int x;
		int y;
		int z;
		void *mlx;
		void *win;
		int size;
}				t_params;

int close_pls(void *param)
{
	(void)param;
	exit(0);
}

int	draw_line(t_params *p, int length, int direction)
{
	int tmp;

	tmp = -1;
	while (++tmp < length)
	{
		if (direction == 1)
			p->y -= 1;
		else if (direction == 2)
		{
			p->y -= 1;
			p->x += 1;
		}
		else if (direction == 3)
			p->x += 1;
		else if (direction == 4)
		{
			p->y += 1;
			p->x += 1;
		}
		else if (direction == 5)
			p->y += 1;
		else if (direction == 6)
		{
			p->y += 1;
			p->x -= 1;
		}
		else if (direction == 7)
			p->x -= 1;
		else if (direction == 8)
		{
			p->y -= 1;
			p->x -= 1;
		}
		mlx_pixel_put(p->mlx, p->win, p->x, p->y, p->color);
	}
	return (0);
}

void	draw_box(t_params *p)
{
	int x;
	int y;

	x = p->x;
	y = p->y;
	draw_line(p, p->size, 1);
	draw_line(p, p->size, 3);
	draw_line(p, p->size / 2, 2);
	draw_line(p, p->size, 7);
	draw_line(p, p->size / 2, 6);
	p->x = x;
	p->y = y;
	draw_line(p, p->size, 3);
	draw_line(p, p->size, 1);
	p->y = y;
	draw_line(p, p->size / 2, 2);
	draw_line(p, p->size, 1);
	p->x = x;
	p->y = y;
}

void	add_r(t_params *p)
{
	if ((unsigned int)p->color < 0xFF0000)
		p->color += (int)(4UL << 16UL);
}

void	add_g(t_params *p)
{
	if (((unsigned int)p->color & 0xFF00UL) < 0xFF00L)
		p->color += (int)(4UL << 8UL);
}

void	add_b(t_params *p)
{
	if (((unsigned int)p->color & 0xFFUL) < 0xFFUL)
		p->color += (int)(4UL << 0UL);
}

void	rem_r(t_params *p)
{
	if ((unsigned int)p->color > 0x40000UL)
		p->color -= (int)(4UL << 16UL);
}

void	rem_g(t_params *p)
{
	if (((unsigned int)p->color & 0xFF00UL) > 0x400UL)
		p->color -= (int)(4UL << 8UL);
}

void	rem_b(t_params *p)
{
	if (((unsigned int)p->color & 0xFFUL) > 0x4UL)
		p->color -= (int)(4UL << 0UL);
}

/*
 * .....
 * .812.
 * .7*3.
 * .654.
 * ....
 */

void	draw_square(t_params *p)
{
	int x;

	x = p->x;
	p->x += p->size * 5;
	draw_line(p, p->size * 1, 3);
	draw_line(p, p->size * 1, 1);
	draw_line(p, p->size * 1, 7);
	draw_line(p, p->size * 1, 5);

	p->x = x;
}

void	draw_two(t_params *p)
{
	int x;

	x = p->x;
	p->x += p->size * 5;
	draw_line(p, p->size * 3, 3);
	draw_line(p, p->size * 3, 5);
	draw_line(p, p->size * 2, 7);
	draw_line(p, p->size * 1, 5);
	draw_line(p, p->size * 2, 3);
	draw_line(p, p->size * 1, 5);
	draw_line(p, p->size * 3, 7);
	draw_line(p, p->size * 3, 1);
	draw_line(p, p->size * 2, 3);
	draw_line(p, p->size * 1, 1);
	draw_line(p, p->size * 2, 7);
	draw_line(p, p->size * 1, 1);
	p->x = x;
}

void	draw_four(t_params *p)
{
	draw_line(p, p->size * 3, 5);
	draw_line(p, p->size * 2, 3);
	draw_line(p, p->size * 2, 5);
	draw_line(p, p->size * 1, 3);
	draw_line(p, p->size * 2, 1);
	draw_line(p, p->size * 1, 3);
	draw_line(p, p->size * 1, 1);
	draw_line(p, p->size * 1, 7);
	draw_line(p, p->size * 2, 1);
	draw_line(p, p->size * 1, 7);
	draw_line(p, p->size * 2, 5);
	draw_line(p, p->size * 1, 7);
	draw_line(p, p->size * 2, 1);
	draw_line(p, p->size * 1, 7);
}

void	draw_rgb(t_params *p, int where)
{
	int x;
	int y;

	x = p->x;
	y = p->y;
	mlx_string_put(p->mlx, p->win, 10, where, 0xFF0000, "red");
	p->x = 75;
	p->y = where + 10;
	draw_line(p, (p->color / 0x10000) * 4,3);
	mlx_string_put(p->mlx, p->win, 10, where - 15, 0x00FF00, "green");
	p->x = 75;
	p->y = where - 5;
	draw_line(p, (p->color % 0x10000 / 0x100) * 4,3);
	mlx_string_put(p->mlx, p->win, 10, where - 30, 0x0000FF, "blue");
	p->x = 75;
	p->y = where - 20;
	draw_line(p, (p->color % 0x100) * 4,3);
	p->x = x;
	p->y = y;
}

/*
 * .....
 * .812.
 * .7*3.
 * .654.
 * ....
 */
/*
void rotate(t_params *p, int axis, int dir)
{

}*/

void	draw_four_pixels(t_fdf *fdf)
{
	t_pixel		*p;
	int			i;

	i = 0;
	p = ((t_pixel *)&fdf->map.bit_map.items[i]);
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, i % fdf->map.width * fdf->mutation.stretch.x + fdf->mutation.shift.x, i / fdf->map.width * fdf->mutation.stretch.y + fdf->mutation.shift.y, p->color);
	++i;
	p = ((t_pixel *)&fdf->map.bit_map.items[i]);
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, i % fdf->map.width * fdf->mutation.stretch.x + fdf->mutation.shift.x, i / fdf->map.width * fdf->mutation.stretch.y + fdf->mutation.shift.y, p->color);
	i = fdf->map.width;
	p = ((t_pixel *)&fdf->map.bit_map.items[i]);
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, i % fdf->map.width * fdf->mutation.stretch.x + fdf->mutation.shift.x, i / fdf->map.width * fdf->mutation.stretch.y + fdf->mutation.shift.y, p->color);
	++i;
	p = ((t_pixel *)&fdf->map.bit_map.items[i]);
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, i % fdf->map.width * fdf->mutation.stretch.x + fdf->mutation.shift.x, i / fdf->map.width * fdf->mutation.stretch.y + fdf->mutation.shift.y, p->color);
}

/*
 * .....
 * .812.
 * .7*3.
 * .654.
 * ....
 */

int	change_color_when_press_up_arrow(int code, void *fdf)
{
	if (code == 126)
		((t_fdf *)fdf)->mutation.shift.y -= 10;
	else if (code == 125)
		((t_fdf *)fdf)->mutation.shift.y += 10;
	else if (code == 124)
		((t_fdf *)fdf)->mutation.shift.x += 10;
	else if (code == 123)
		((t_fdf *)fdf)->mutation.shift.x -= 10;
	/*else if (code == 24)
		((t_fdf *)fdf)->mutation.shift.size += 1;
	else if (code == 27)
	{
		if (((t_params *)p)->size < 2)
			((t_params *)p)->size = 1;
		else
			((t_params *)p)->size -= 1;
	}
	else if (code == 83)
		rem_r((t_params *)p);
	else if (code == 84)
		rem_g((t_params *)p);
	else if (code == 85)
		rem_b((t_params *)p);
	else if (code == 86)
		add_r((t_params *)p);
	else if (code == 87)
		add_g((t_params *)p);
	else if (code == 88)
		add_b((t_params *)p);*/
	else if (code == 53)
		close_pls(NULL);
	/*else if (code == 13)
		rotate(p, X_AXIS, ROT_R);*/

	printf("Code recognized: %i\n", code/*, ((t_params *)p)->x, ((t_params *)p)->y, ((t_params *)p)->color*/);
	mlx_clear_window(((t_fdf *)fdf)->mlx.mlx, ((t_fdf *)fdf)->mlx.win);

	draw_four_pixels((t_fdf *)fdf);

	//mlx_string_put(((t_params *)p)->mlx, ((t_params *)p)->win, 1300, 1150, 0xFFFFFF, ft_itoa(((t_params *)p)->x));
	//mlx_string_put(((t_params *)p)->mlx, ((t_params *)p)->win, 1350, 1150, 0xFFFFFF, ft_itoa(((t_params *)p)->y));
	//mlx_string_put(((t_params *)p)->mlx, ((t_params *)p)->win, 1450, 1150, 0xFFFFFF, ft_itoa(((t_params *)p)->size));

	//mlx_pixel_put(((t_params *)p)->mlx, ((t_params *)p)->win, ((t_params *)p)->x, ((t_params *)p)->y, ((t_params *)p)->color);
	//draw_box(p);
	//draw_four(p);
	//draw_two(p);
	//draw_square(p);
	//draw_rgb(p, 1150);
	return (0);
}

int early_mlx_init(t_fdf *fdf)
{
	t_pixel *p;


	p = ((t_pixel *)&fdf->map.bit_map.items[0]);
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 0, 0x00FFFF00, "Mlx initializing complete!");
	fdf->mutation.shift.x = 300;
	fdf->mutation.shift.y = 300;
	fdf->mutation.stretch.x = 100;
	fdf->mutation.stretch.y = 100;

	draw_four_pixels(fdf);

	/*
	p.x = 300;
	p.y = 300;
	p.size = 100;
	p.color = 0xFFFFFF;
	mlx_string_put(p.mlx, p.win, 300, 300, 0x00FFFF00, "Hey!");*/
	mlx_hook(fdf->mlx.win, 2, 1UL << 0UL, change_color_when_press_up_arrow, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_pls, NULL);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}