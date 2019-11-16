/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:53:18 by ftothmur          #+#    #+#             */
/*   Updated: 2019/11/16 20:11:17 by ftothmur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void            shift_x(t_fdf *fdf, int shift_value)
{
    fdf->mutation.shift.x += shift_value;
    return ;
}

void            shift_y(t_fdf *fdf, int shift_value)
{
    fdf->mutation.shift.y += shift_value;
    return ;
}

void            shift_z(t_fdf *fdf, int shift_value)
{
    fdf->mutation.shift.z += shift_value;
    return ;
}

void            rotate_along_the_x_axis(t_fdf *fdf, int rotation_value)
{

    return ;
}

void            count_coordinate_changes(t_fdf *fdf, t_position *chages)
{
    t_mutation  *m;

    m = fdf->mutation;
    changes.x = m->stretch.x + m->
    return ;
}

int             mutate(t_fdf *fdf, )
{
    t_position  chages;

    count_coordinate_changes(fdf, &chages);

    x = stretch(fdf, 'x') * tilt(fdf, 'x') * origin_curr(x) + shift(fdf, 'x');
    y = stretch(fdf, 'y') * tilt(fdf, 'y') * y + shift(fdf, 'y');
    z = stretch(fdf, 'z') * tilt(fdf, 'z') * x + shift(fdf, 'z');

    ((Xo)*cos(Ly)+(-Yo*sin(Lx)+Zo*cos(Lx))*sin(Ly))*cos(Lz)-((Yo*cos(Lx)+Zo*sin(Lx)))*sin(Lz)
-((Xo)*cos(Ly)+(-Yo*sin(Lx)+Zo*cos(Lx))*sin(Ly))*sin(Lz)+((Yo*cos(Lx)+Zo*sin(Lx)))*cos(Lz)
(-(Xo)*sin(Ly)+(-Yo*sin(Lx)+Zo*cos(Lx))*cos(Ly))
    return (SUCCESS);
}