/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:05:20 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/13 18:17:08 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int				main(void)
{
	t_pixel		i;

	i.z = 20;
	i.color = 20;
	printf("%lu\n%lu\n%i\n%i\n", sizeof(t_pixel), sizeof(i), i.z, i.color);
	return (0);
}
