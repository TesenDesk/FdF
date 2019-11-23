/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:22:32 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 03:49:41 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					usage(void)
{
	ft_putendl("USAGE");
	return (FAILURE);
}

int					error(char *error_msg)
{
	ft_putendl(error_msg);
	return (FAILURE);
}

int					use_terminal_arguments_to_open_a_file(int argc, char **argv,
						t_read *reader)
{
	if (argc != 2)
		return (usage());
	if ((reader->fd = open(*(argv + 1), O_RDONLY)) < 0)
		return (error("EBADFD"));
	return (SUCCESS);
}

int					prepare_storage_for_reading_lines(t_read *reader)
{
	if (ft_vector_init(&reader->lines))
		return (FAILURE);
	return (SUCCESS);
}

int					prepare_storage_for_recognized_map_information(
						t_map *map)
{
	if (ft_vector_init(&map->bit_map))
		return (FAILURE);
	return (SUCCESS);
}
void				clear_work_structure(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(*fdf));
	return ;
}

int					read_a_line_and_put_it_into_an_array(t_read *reader)
{
	char			*line;

	if ((reader->read_state = ft_get_next_line(reader->fd, &line)) > 0 &&
			!ft_vector_add(&reader->lines, (void *)line))
		return (SUCCESS);
	return (FAILURE);
}
void				move_top_to_the_beginning_of_the_read_line(char *line,
						char **top)
{
	*top = line;
	return ;
}

// void				move_top_to_expected_number_substr(char **top)
// {
// 	*top = (char *)ft_spskip((const char *)*top);
// 	return ;
// }

// void				convert_substr_to_applicate(char *top, t_pixel *pixel)
// {
// 	pixel->z = ft_atoi(top);
// 	return ;
// }

void				move_top_out_of_substring_number(char **top)
{
	char			*str;

	str = *top;
	while (ft_isdigit(*str) || *str == '+' || *str == '-')
		++str;
	*top = str;
	return ;
}

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

// void				move_top_out_of_color_substring(char **top)
// {
// 	char			*str;

// 	str = *top;
// 	while (*str && !ft_isspace(*str))
// 		++str;
// 	*top = str;
// 	//TODO: не отслеживает неожиданный конец строки.
// 	return ;
// }

int					enter_application_and_color_data(t_fdf *fdf,
						void *pixel_as_ptr)
{
	t_vector		*v;

	v = &fdf->map.bit_map;
	if (ft_vector_add(v, pixel_as_ptr))
		return (FAILURE);
	return (SUCCESS);
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

void 				set_the_largest_abscissa(t_fdf *fdf)
{
	fdf->map.width = fdf->map.bit_map.total;
	return ;
}

int					parse_applicate(char **top, t_pixel *pixel)
{
	char			*tip;
	intmax_t		z;
	
	if (ft_str_to_intmax(*top, &tip, 10, &z))
		return (FAILURE);
	*top = tip;
	pixel->z = (int)z;
	return (SUCCESS);
}

int					parse_first_line_and_recognizing_the_max_abscissa(
						t_fdf *fdf)
{
	char			*top;
	t_remake		converter;

	move_top_to_the_beginning_of_the_read_line(fdf->reader.lines.items[0],
		&top);
	while (*top)
	{
		if (parse_applicate(&top, &converter.pixel))
			return (FAILURE);
		// move_top_out_of_substring_number(&top);
		if (has_color_characteristic(*top))
		{
			if (convert_string_to_color_number(&top, &converter.pixel))
				return (FAILURE);
			// move_top_out_of_color_substring(&top);
		}
		else
			set_default_color(&converter.pixel);
		enter_application_and_color_data(fdf, converter.pixel_as_ptr);
		record_applicate_extremes(fdf);
	}
	set_the_largest_abscissa(fdf);
	return (SUCCESS);
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



int					parse_the_line(t_fdf *fdf)
{
	char			*top;
	t_remake		converter;
	int				x_counter;

	move_top_to_the_beginning_of_the_read_line(
		(char *)ft_vector_get_curr(&fdf->reader.lines), &top);
	if (!top)
		return (FAILURE);
	set_the_abscissa_counter(&x_counter, fdf);
	while (*top && x_counter--)
	{
		if (parse_applicate(&top, &converter.pixel))
			return (FAILURE);
		// move_top_to_expected_number_substr(&top);
		// convert_substr_to_applicate(top, &converter.pixel);
		// move_top_out_of_substring_number(&top);
		if (has_color_characteristic(*top))
		{
			if (convert_string_to_color_number(&top, &converter.pixel))
				return (FAILURE);
		}
		else
			set_default_color(&converter.pixel);
		enter_application_and_color_data(fdf, converter.pixel_as_ptr);
	}
	set_the_largest_ordinate(fdf);
	return (SUCCESS);	
}

int					parse_remaining_lines_and_recognizing_the_max_ordinate(
						t_fdf *fdf)
{
	while (fdf->reader.read_state > NO_MORE_LINES)
	{
		if (
				read_a_line_and_put_it_into_an_array(&fdf->reader) ||
				parse_the_line(fdf))
			return (FAILURE);
	}
	if (fdf->reader.read_state == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

void				count_applicate(t_fdf *fdf)
{
	fdf->map.length = (fdf->reader.z_max - fdf->reader.z_min);
	return ;
}

int					read_and_parse_the_file(t_fdf *fdf)
{
	read_a_line_and_put_it_into_an_array(&fdf->reader);
	parse_first_line_and_recognizing_the_max_abscissa(fdf);
	parse_remaining_lines_and_recognizing_the_max_ordinate(fdf);
	count_applicate(fdf);
	return (SUCCESS);
}

int					validate_read_and_parse(int argc, char **argv, t_fdf *fdf)
{
	clear_work_structure(fdf);
	if (
			!use_terminal_arguments_to_open_a_file(argc, argv, &fdf->reader) &&
			!prepare_storage_for_reading_lines(&fdf->reader) &&
			!prepare_storage_for_recognized_map_information(&fdf->map) &&
			!read_and_parse_the_file(fdf))
		return (SUCCESS);
	return (FAILURE);
}