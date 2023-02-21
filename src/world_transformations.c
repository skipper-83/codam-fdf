/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:32:44 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/21 10:37:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_world(t_meta *m, float angle, char axis)
{
	apply_rotate(&m->world, m->transformer, angle, axis);
	create_new_image(m);
}

void	scale_world(t_meta *m, float x, float y, float z)
{
	m44_scale(m->world, x, y, z);
	create_new_image(m);
}

void	translate_world(t_meta *m, float x, float y, float z)
{
	m44_translate(m->world, x, y, z);
	create_new_image(m);
}
