/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 05:28:51 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 09:40:26 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				move_to_nbr(char **top)
{
	while (ft_isspace(**top))
		++(*top);
	return ;
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
		move_to_nbr(&top);
		if (!*top)
			break ;
		if (parse_applicate(&top, &converter.pixel))
			return (FAILURE);
		if (has_color_characteristic(*top))
		{
			if (convert_string_to_color_number(&top, &converter.pixel))
				return (FAILURE);
		}
		else
			set_default_color(&converter.pixel);
		enter_application_and_color_data(fdf, converter.pixel_as_ptr);
		record_applicate_extremes(fdf);
	}
	set_the_largest_abscissa(fdf);
	return (SUCCESS);
}

int					parse_the_line(t_fdf *fdf)
{
	char			*top;
	t_remake		converter;
	int				x_counter;

	move_top_to_the_beginning_of_the_read_line(
		(char *)ft_vector_get_curr(&fdf->reader.lines), &top);
	if (!*top)
		return (FAILURE);
	set_the_abscissa_counter(&x_counter, fdf);
	while (*top && x_counter--)
	{
		move_to_nbr(&top);
		if (!top)
			return (FAILURE);
		if (parse_applicate(&top, &converter.pixel))
			return (FAILURE);
		if (has_color_characteristic(*top))
		{
			if (convert_string_to_color_number(&top, &converter.pixel))
				return (FAILURE);
		}
		else
			set_default_color(&converter.pixel);
		enter_application_and_color_data(fdf, converter.pixel_as_ptr);
	}
	if (x_counter > 0)
		return (FAILURE);
	set_the_largest_ordinate(fdf);
	return (SUCCESS);
}

int					parse_remaining_lines_and_recognizing_the_max_ordinate(
						t_fdf *fdf)
{
	while (fdf->reader.read_state > NO_MORE_LINES)
	{
		if (read_a_line_and_put_it_into_an_array(&fdf->reader) ||
				parse_the_line(fdf))
		{
			if (!fdf->reader.read_state)
				break ;
			return (FAILURE);
		}
	}
	if (fdf->reader.read_state == ERROR)
		return (FAILURE);
	return (SUCCESS);
}

int					read_and_parse_the_file(t_fdf *fdf)
{
	if (read_a_line_and_put_it_into_an_array(&fdf->reader) ||
			parse_first_line_and_recognizing_the_max_abscissa(fdf) ||
			parse_remaining_lines_and_recognizing_the_max_ordinate(fdf))
		return (error("ERROR"));
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
