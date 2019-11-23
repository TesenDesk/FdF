/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_and_error_management.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 05:23:33 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/23 05:25:13 by ftothmur         ###   ########.fr       */
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

int					read_a_line_and_put_it_into_an_array(t_read *reader)
{
	char			*line;

	if ((reader->read_state = ft_get_next_line(reader->fd, &line)) > 0 &&
			!ft_vector_add(&reader->lines, (void *)line))
		return (SUCCESS);
	return (FAILURE);
}
