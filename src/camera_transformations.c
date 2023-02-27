/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:38:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 22:20:33 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_rotation_var(t_angle *r_var, float angle, char axis)
{
	if (axis == 'x')
		r_var->x += angle;
	if (axis == 'y')
		r_var->y += angle;
	if (axis == 'z')
		r_var->z += angle;
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
	create_new_image(m);
}

void	reset_cam(t_meta *m)
{
	m44_to_identity_matrix(m->world);
	m44_to_identity_matrix(m->camera);
	if (m->projection == PARALLEL)
	{
		scale_world(m, 10.0 / m->drawing_w, \
					10.0 / m->drawing_w, 10.0 / m->drawing_w);
		apply_rotate(&m->camera, m->transformer, 90, 'z');
	}
	else
	{
		m44_translate(m->camera, 0, 0, m->drawing_h * -4);
		apply_rotate(&m->camera, m->transformer, 225, 'z');
	}
	if (m->camera == NULL)
		exit_error(ERROR_MEM, m);
	apply_rotate(&m->camera, m->transformer, 180, 'x');
	if (m->camera == NULL)
		exit_error(ERROR_MEM, m);
	m->cam_rotation.z = -45;
	m->cam_rotation.x = 0;
	m->cam_rotation.y = 0;
	m->world_rotation.x = 0;
	m->world_rotation.y = 0;
	m->world_rotation.z = 0;
	create_new_image(m);
}
