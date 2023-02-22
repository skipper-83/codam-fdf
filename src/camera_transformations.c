/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:38:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 22:37:29 by albertvanan      ###   ########.fr       */
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
	create_new_image(m);
}

void	reset_cam(t_meta *m)
{
	float	coeff;
	int		z_rotate;

	m44_to_identity_matrix(m->world);
	m44_to_identity_matrix(m->camera);
	z_rotate = 135;
	if (m->projection == PARALLEL)
		z_rotate = 315;
	apply_rotate(&m->camera, m->transformer, 180, 'x');
	m->cam_rotation.x = 180;
	apply_rotate(&m->camera, m->transformer, z_rotate, 'z');
	m->cam_rotation.z = z_rotate;
	coeff = m->drawing_w;
	if (m->drawing_d * .3 > m->drawing_w)
		coeff = m->drawing_d * .3;
	m44_translate(m->camera, 0, 0, (coeff) * 1.8);
	create_new_image(m);
}
