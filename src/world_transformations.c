/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:32:44 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 15:41:33 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_world(t_meta *m, float angle, char axis)
{
	apply_rotate(&m->world, m->transformer, angle, axis);
	if (m->world == NULL)
		exit_error(ERROR_MEM, m);
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
