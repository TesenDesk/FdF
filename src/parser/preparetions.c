/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparetions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 05:21:32 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 09:39:50 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		return (error("ERROR"));
	return (SUCCESS);
}

int					prepare_storage_for_recognized_map_information(
						t_map *map)
{
	if (ft_vector_init(&map->bit_map))
		return (error("ERROR"));
	return (SUCCESS);
}

void				clear_work_structure(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(*fdf));
	return ;
}