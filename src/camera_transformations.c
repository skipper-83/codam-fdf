/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:38:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 15:41:13 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_rotation_var(t_angle *rotation_var, float angle, char axis)
{
	if (axis == 'x')
		rotation_var->x += angle;
	if (axis == 'y')
		rotation_var->y += angle;
	if (axis == 'z')
		rotation_var->z += angle;
}

void	apply_rotate(float ***target, float **rotator, float angle, char axis)
{
	m44_to_identity_matrix(rotator);
	m44_rotate(rotator, angle, axis);
	*target = m44_dot_product(*target, rotator, FREE_M1);
}

void	translate_cam(t_meta *m, float x, float y, float z)
{
	m44_translate(m->camera, x, y, z);
	create_new_image(m);
}

void	rotate_cam(t_meta *m, float angle, char axis)
{
	apply_rotate(&m->camera, m->transformer, angle, axis);
	if (m->camera == NULL)
		exit_error(ERROR_MEM, m);
	update_rotation_var(&m->cam_rotation, angle, axis);
	ft_printf("rotations: %f, %f\n", m->cam_rotation.x, m->cam_rotation.y);
	create_new_image(m);
}
