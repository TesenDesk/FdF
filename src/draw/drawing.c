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

typedef struct	s_wire
{
	t_cordcase	from;
	t_cordcase	to;
	int		dx;
	int		dy;
	int		sign_x;
	int		sign_y;
}				t_wire;

int close_pls(void *param)
{
	(void)param;
	exit(0);
}

/*
int		y_rotation(t_fdf *f, int x_map, int y_map, int z_map)
{
	int y;
	double rad;

	rad = f->mutation.tilt.z * PI / 180;
	y = ((int)(x_map * sin(rad) * MULTIPLIER) +
		 (int)(y_map * cos(rad) * MULTIPLIER)) /
		MULTIPLIER;


	rad = f->mutation.tilt.y * PI / 180;
	y = y + ((int)(x_map * cos(rad) * MULTIPLIER) +
			 (int)(z_map * sin(rad) * MULTIPLIER)) /
			MULTIPLIER;

	rad = f->mutation.tilt.x * PI / 180;
	y = y + ((int)(y_map * cos(rad) * MULTIPLIER) +
			 (int)(z_map * -sin(rad) * MULTIPLIER)) /
			MULTIPLIER;
	return (y);
}

int		get_y_pc(t_fdf *f, int i)
{
	int		y;
	t_remake r;


	r.pixel_as_ptr = f->map.bit_map.items[i];

	y = y_rotation(f, i % f->map.width * f->mutation.stretch.x -
					((f->map.width - 1) * f->mutation.stretch.x / 2),
					i / f->map.width * f->mutation.stretch.y -
					((f->map.height - 1) * f->mutation.stretch.y / 2),
					r.pixel.z * f->mutation.stretch.z -
					((f->map.height - 1) * f->mutation.stretch.z / 2));

	y += f->mutation.shift.y;
	return (y);
}

int		x_rotation(t_fdf *f, int x_map, int y_map, int z_map)
{
	int x;
	double rad;

	rad = f->mutation.tilt.z * PI / 180;
	x = ((int)(x_map * cos(rad) * MULTIPLIER) +
			(int)(y_map * -sin(rad) * MULTIPLIER)) /
			MULTIPLIER;

	rad = f->mutation.tilt.y * PI / 180;
	x = x + ((int)(x_map * cos(rad) * MULTIPLIER) +
			(int)(z_map * sin(rad) * MULTIPLIER)) /
			MULTIPLIER;

	rad = f->mutation.tilt.x * PI / 180;
	x = x + ((int)(y_map * sin(rad) * MULTIPLIER) +
			(int)(z_map * cos(rad) * MULTIPLIER)) /
			MULTIPLIER;
	return (x);
}

int		get_x_pc(t_fdf *f, int i)
{
	int		x;
	t_remake r;


	r.pixel_as_ptr = f->map.bit_map.items[i];

	x = x_rotation(f, i % f->map.width * f->mutation.stretch.x -
					((f->map.width - 1) * f->mutation.stretch.x / 2),
					i / f->map.width * f->mutation.stretch.y -
					((f->map.height - 1) * f->mutation.stretch.y / 2),
					r.pixel.z * f->mutation.stretch.z);

	x += f->mutation.shift.x;
	return (x);
}
*/

void	perform_potation(t_fdf *fdf, int i, t_cordcase *ret)
{
	long x_map; // положение точки на карте
	long y_map;
	long z_map;
	t_remake r; // какая-то непонятная дичь
	long double x_rad; // вращение (сразу в радианах (чобы и нет))
	long double y_rad;
	long double z_rad;
	long x_shift; // зум (расстояние между двумя соседними тощками
	long y_shift;
	long z_shift; // HUH? по z собрался двигать? por favor?
	long x_stretch; // смещение карты относительно чего-нибудь
	long y_stretch;
	long z_stretch;
	long x; // а это короч координты пикселя (то, что нужно нарисоватт)
	long y;
	long z; // хз хачем тут z но пусть будет
	int color;

	//Получаем координаты точки с карты! НЕ координты пикселя!!!!1111
	x_map = i % fdf->map.width;
	y_map = i / fdf->map.width;
	r.pixel_as_ptr = fdf->map.bit_map.items[i];
	z_map = r.pixel.z;
	color = r.pixel.color;

	// Задаем параметры, мать их
	x_stretch = fdf->mutation.stretch.x;
	y_stretch = fdf->mutation.stretch.y;
	z_stretch = fdf->mutation.stretch.z;
	x_shift = fdf->mutation.shift.x;
	y_shift = fdf->mutation.shift.y;
	z_shift = fdf->mutation.shift.z;
	x_rad = fdf->mutation.tilt.x * PI / 180;
	y_rad = fdf->mutation.tilt.y * PI / 180;
	z_rad = fdf->mutation.tilt.z * PI / 180;

	// Применяем СТРЕТЧ на координаты карты (они становятся промежуточными переменными)
	x_map *= x_stretch;
	y_map *= y_stretch;
	z_map = z_map * z_stretch / 2;

	// Добавляем щепотку смещения осей в центр композийшон

	x_map -= (fdf->map.width - 1) * x_stretch / 2;
	y_map -= (fdf->map.height - 1) * y_stretch / 2;
	//z_map += (fdf->map.length - 1) * z_stretch / 2;

	// Поворот по оси ЫКС

	x = x_map;
	y = (long)((y_map * cosl(x_rad) * MULTIPLIER) - (z_map * sinl(x_rad)) * MULTIPLIER) / MULTIPLIER;
	z = (long)((y_map * sinl(x_rad) * MULTIPLIER) + (z_map * cosl(x_rad)) * MULTIPLIER) / MULTIPLIER;

	// Поворот по оси ЫГРЫК

	x_map = x;
	x = (long)((x_map * cosl(y_rad) * MULTIPLIER) + (z * sinl(y_rad)) * MULTIPLIER) / MULTIPLIER;
	y = y;
	//z = (long)((x_map * -sinl(y_rad) * MULTIPLIER) + (z * cosl(y_rad)) * MULTIPLIER) / MULTIPLIER;

	// Поворот по оси ЗЕД

	x_map = x;
	y_map = y;
	x = (long)((x_map * cosl(z_rad) * MULTIPLIER) - (y_map * sinl(z_rad) * MULTIPLIER)) / MULTIPLIER;
	y = (long)((x_map * sinl(z_rad) * MULTIPLIER) + (y_map * cosl(z_rad) * MULTIPLIER)) / MULTIPLIER;
	//z = z; // Z больше не нужОн, можем не писать его дальше!

	x = (x * fdf->mutation.stretch.range) / 100;
	y = (y * fdf->mutation.stretch.range) / 100;

	// Двигаем коордынаты на смещение!

	x += x_shift;
	y += y_shift;
	//z += z_shift;

	// Запихиваем полученные данные в ж.. структуру!!!

	ret->x = (int)x;
	ret->y = (int)y;
}
/*
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
 */
/*
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
*/
/*
 * .....
 * .812.
 * .7*3.
 * .654.
 * ....
 */
/*
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
*/
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


double	ft_dabs(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}


void	draw_line_between(t_fdf *fdf, t_wire *w)
{
	int e;
	int ee;
	int x;
	int y;

	w->dy *= -1;
	x = w->from.x;
	y = w->from.y;
	e = w->dx + w->dy;
	mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, w->to.x, w->to.y, DEFAULT_COLOR);
	while (x != w->to.x || y != w->to.y)
	{
		mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, x, y, DEFAULT_COLOR);
		ee = e * 2;
		if (ee >= w->dy)
		{
			x += w->sign_x;
			e += w->dy;
		}
		if (ee <= w->dx)
		{
			y += w->sign_y;
			e += w->dx;
		}
	}
}

int		need_to_draw_this(t_fdf *fdf, t_wire *w)
{
	if ((w->from.x >= 0 && w->from.x < SCREEN_WIDTH &&
			w->from.y >= 0 && w->from.y < SCREEN_HEIGHT) ||
			(w->to.x >= 0 && w->to.x < SCREEN_WIDTH &&
			w->to.y >= 0 && w->to.y < SCREEN_HEIGHT))
		return (1);
	return (0);
}

void	draw_connections_to_neighbours(t_fdf *fdf, int pos)
{
	t_wire		w;
	int			tmp;
	int			i;

	i = 0;
	perform_potation(fdf, pos, &w.from);
	while (++i <= 2)
	{
		if (i == 1 &&
				(tmp = pos + fdf->map.width) / fdf->map.width < fdf->map.height)
			perform_potation(fdf, tmp, &w.to);
		else if (i == 2 && (pos + 1) % fdf->map.width &&
			(tmp = pos + 1) / fdf->map.width <= fdf->map.height)
			perform_potation(fdf, tmp, &w.to);
		if (need_to_draw_this(fdf, &w))
		{
			w.dx = abs(w.to.x - w.from.x);
			w.dy = abs(w.to.y - w.from.y);
			w.sign_x = w.from.x > w.to.x ? -1 : 1;
			w.sign_y = w.from.y > w.to.y ? -1 : 1;
			draw_line_between(fdf, &w);
		}
	}
}

void	draw_four_pixels(t_fdf *fdf)
{
	//t_pixel		*p;
	int			i;

	i = -1;

	//mlx_pixel_put(fdf->mlx.mlx, fdf->mlx.win, get_x_pc(fdf, i), get_y_pc(fdf, i), p->color);
	while (++i < fdf->map.size)
		draw_connections_to_neighbours(fdf, i);
}

/*
 * .....
 * .812.
 * .7*3.
 * .654.
 * ....
 */

void	change_range(t_fdf *fdf, int mode)
{
	int *range;

	range = &fdf->mutation.stretch.range;
	if (!mode)
		*range = DEFAULT_RANGE;
	else
	{
		*range += CHANGE_RANGE * mode;
		if (*range > MAX_RANGE)
			*range = MAX_RANGE;
		else if (*range < MIN_RANGE)
			*range = MIN_RANGE;
	}
}

void	change_stretch(t_fdf *fdf, int x_mode, int y_mode, int z_mode)
{
	int	tmp;

	if (!x_mode && !y_mode && !z_mode)
	{
		fdf->mutation.stretch.x = DEFAULT_STRETH;
		fdf->mutation.stretch.y = DEFAULT_STRETH;
		fdf->mutation.stretch.z = DEFAULT_STRETH;
		return ;
	}
	if ((tmp = fdf->mutation.stretch.x + CHANGE_STRETCH * x_mode) > 0)
		fdf->mutation.stretch.x = tmp;
	if ((tmp = fdf->mutation.stretch.y + CHANGE_STRETCH * y_mode) > 0)
		fdf->mutation.stretch.y = tmp;
	if ((tmp = fdf->mutation.stretch.z + CHANGE_STRETCH * z_mode) >= 0)
		fdf->mutation.stretch.z = tmp;
}

void change_rotate(t_fdf *fdf, int x_mode, int y_mode, int z_mode)
{
	t_tilt	*tilt;

	tilt = &fdf->mutation.tilt;

	if (!x_mode && !y_mode && !z_mode)
	{
		tilt->x = DEFAULT_ROTATE;
		tilt->y = DEFAULT_ROTATE;
		tilt->z = DEFAULT_ROTATE;
		return ;
	}
	tilt->x += CHANGE_ROTATE * x_mode;
	tilt->y += CHANGE_ROTATE * y_mode;
	tilt->z += CHANGE_ROTATE * z_mode;
	if (tilt->x >= MAX_ROTATE)
		tilt->x -= MAX_ROTATE;
	else if (tilt->x < MIN_ROTATE)
		tilt->x += MAX_ROTATE;
	if (tilt->y >= MAX_ROTATE)
		tilt->y -= MAX_ROTATE;
	else if (tilt->y < MIN_ROTATE)
		tilt->y += MAX_ROTATE;
	if (tilt->z >= MAX_ROTATE)
		tilt->z -= MAX_ROTATE;
	else if (tilt->z < MIN_ROTATE)
		tilt->z += MAX_ROTATE;
}

int	change_color_when_press_buttons(int code, void *vfdf)
{
	t_fdf *fdf = (t_fdf *)vfdf;

	if (code == UP)
		fdf->mutation.shift.y -= CHANGE_MOVE;
	else if (code == DOWN)
		fdf->mutation.shift.y += CHANGE_MOVE;
	else if (code == RIGHT)
		fdf->mutation.shift.x += CHANGE_MOVE;
	else if (code == LEFT)
		fdf->mutation.shift.x -= CHANGE_MOVE;
	else if (code == PLUS)
		change_range(fdf, 1);
	else if (code == MINUS)
		change_range(fdf, -1);

	else if (code == ZOOM_RESET)
		change_stretch(fdf, 0, 0, 0);
	else if (code == ZOOM_X_PLUS)
		change_stretch(fdf, 1, 0, 0);
	else if (code == ZOOM_X_MINUS)
		change_stretch(fdf, -1, 0, 0);
	else if (code == ZOOM_Y_PLUS)
		change_stretch(fdf, 0, 1, 0);
	else if (code == ZOOM_Y_MINUS)
		change_stretch(fdf, 0, -1, 0);
	else if (code == ZOOM_Z_PLUS)
		change_stretch(fdf, 0, 0, 1);
	else if (code == ZOOM_Z_MINUS)
		change_stretch(fdf, 0, 0, -1);

	else if (code == ROTATE_Z_MINUS)
		change_rotate(fdf, 0, 0, -1);
	else if (code == ROTATE_Z_PLUS)
		change_rotate(fdf, 0, 0, 1);
	else if (code == ROTATE_Y_MINUS)
		change_rotate(fdf, 0, -1, 0);
	else if (code == ROTATE_Y_PLUS)
		change_rotate(fdf, 0, 1, 0);
	else if (code == ROTATE_X_MINUS)
		change_rotate(fdf, -1, 0, 0);
	else if (code == ROTATE_X_PLUS)
		change_rotate(fdf, 1, 0, 0);
	else if (code == ROTATE_RESET)
		change_rotate(fdf, 0, 0, 0);




	/*else if (code == 83)
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

	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	char huh[12];
	draw_four_pixels(fdf);

	ft_itostr(fdf->mutation.tilt.x, huh);
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 0, WHITE_COLOR, "position:");
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 100, 0, WHITE_COLOR, ft_itostr(fdf->mutation.shift.x, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 140, 0, WHITE_COLOR, ft_itostr(fdf->mutation.shift.y, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 180, 0, WHITE_COLOR, ft_itostr(fdf->mutation.shift.z, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 15, WHITE_COLOR, "rotation:");
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 100, 15, WHITE_COLOR, ft_itostr(fdf->mutation.tilt.x, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 140, 15, WHITE_COLOR, ft_itostr(fdf->mutation.tilt.y, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 180, 15, WHITE_COLOR, ft_itostr(fdf->mutation.tilt.z, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 30, WHITE_COLOR, "stretch:");
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 100, 30, WHITE_COLOR, ft_itostr(fdf->mutation.stretch.x, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 140, 30, WHITE_COLOR, ft_itostr(fdf->mutation.stretch.y, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 180, 30, WHITE_COLOR, ft_itostr(fdf->mutation.stretch.z, huh));
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 45, WHITE_COLOR, "last recognized button code:");
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 300, 45, WHITE_COLOR, ft_itostr(code, huh));

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
	//t_pixel *p;


	//p = ((t_pixel *)&fdf->map.bit_map.items[0]);
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
	mlx_string_put(fdf->mlx.mlx, fdf->mlx.win, 0, 0, 0x00FFFF00, "Mlx initializing complete!");
	fdf->mutation.shift.x = DEFAULT_POS_X;
	fdf->mutation.shift.y = DEFAULT_POS_Y;
	fdf->mutation.stretch.x = DEFAULT_STRETH;
	fdf->mutation.stretch.y = DEFAULT_STRETH;
	fdf->mutation.stretch.z = DEFAULT_STRETH / 2;
	fdf->mutation.stretch.range = DEFAULT_RANGE;
	fdf->map.size = fdf->map.height * fdf->map.width;

	draw_four_pixels(fdf);

	/*
	p.x = 300;
	p.y = 300;
	p.size = 100;
	p.color = 0xFFFFFF;
	mlx_string_put(p.mlx, p.win, 300, 300, 0x00FFFF00, "Hey!");*/
	mlx_hook(fdf->mlx.win, 2, 1UL << 0UL, change_color_when_press_buttons, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_pls, NULL);
	mlx_loop(fdf->mlx.mlx);
	return (0);
}
