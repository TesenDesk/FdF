/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:22:32 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/13 19:09:13 by ftothmur         ###   ########.fr       */
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

int					prepare_storage_for_recognized_card_information(
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

	if ((reader->read_state = ft_getline(reader->fd, &line)) > 0 &&
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

void				move_top_to_expected_number_substr(char **top)
{
	*top = ft_spskip((const char *)*top);
	return ;
}
int					parse_first_line_and_recognizing_the_max_abscissa(
						t_fdf *fdf)
{
	char			*top;
	char			*tip;

	move_top_to_the_beginning_of_the_read_line(fdf->reader.lines.items[0],
		&top);
	move_top_to_expected_number_substr(&top);
	return (SUCCESS);
}

int					read_and_parse_the_file(t_fdf *fdf)
{
	read_a_line_and_put_it_into_an_array(&fdf->reader);
	parse_first_line_and_recognizing_the_max_abscissa(fdf);
	return (SUCCESS);
}

int					validate_read_and_parse(int argc, char **argv, t_fdf *fdf)
{
	clear_work_structure(fdf);
	if (
			!use_terminal_arguments_to_open_a_file(argc, argv, &fdf->reader) &&
			!prepare_storage_for_reading_lines(&fdf->reader) &&
			!prepare_storage_for_recognized_card_information(&fdf->map) &&
			!read_and_parse_the_file(&fdf))
		return (SUCCESS);
	return (FAILURE);
}