/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:53:00 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/12 21:57:01 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int early_mlx_init(t_fdf *fdf);

int					main(int argc, char **argv)
{
	t_fdf			fdf;

	if (validate_read_and_parse(argc, argv, &fdf) == FAILURE)
		return (FAILURE);
	early_mlx_init(&fdf);
	return (SUCCESS);
}