/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:53:00 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 09:36:09 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					main(int argc, char **argv)
{
	t_fdf			fdf;

	if (validate_read_and_parse(argc, argv, &fdf) == FAILURE)
	{
		free_the_project(&fdf);
		return (FAILURE);
	}
	early_mlx_init(&fdf);
	return (SUCCESS);
}