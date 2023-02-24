/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:38:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/24 11:36:37 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_rotation_var(t_angle *r_var, float angle, char axis, t_meta *m)
{
	char	rotation_disp[200];

	if (axis == 'x')
		r_var->x += angle;
	if (axis == 'y')
		r_var->y += angle;
	if (axis == 'z')
		r_var->z += angle;
	// mlx_delete_image(m->mlx, m->rotations);
	// ft_sprintf(rotation_disp, "cam rotation: %.2f %.2f %.2f | world rotation \
	// %.2f %.2f %.2f", m->cam_rotation.x, m->cam_rotation.y, m->cam_rotation.z, \
	// m->world_rotation.x, m->world_rotation.y, m->world_rotation.z);
	// m->rotations = mlx_put_string(m->mlx, rotation_disp, 50, m->window_h - 30);
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
	update_rotation_var(&m->cam_rotation, angle, axis, m);
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
