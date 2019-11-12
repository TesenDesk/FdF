/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:22:32 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/12 21:49:52 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					usage(void)
{
	ft_putendl("USAGE");
	return (FAILURE);
}

int					validate_arguments(int argc, char **argv, t_read *reader)
{
	if (argc != 2)
		return (usage());
	if ((reader->fd = open(*(argv + 1), O_RDONLY)) < 0)
		return (FAILURE);
}

int					read_and_parse(t_read *reader)
{
	ft_getline(fdf)
	return (SUCCESS);
}


int					validate_read_and_parse(int argc, char **argv, t_fdf *fdf)
{
	if (validate_arguments(argc, argv, &fdf->reader) == FAILURE)
		return (FAILURE);
	read_and_parse(&fdf->reader);
	return (SUCCESS);
}