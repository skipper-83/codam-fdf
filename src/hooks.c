/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:53:51 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 23:24:01 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		if (m->projection == PARALLEL)
			m->projection = PERSPECTIVE;
		else
			m->projection = PARALLEL;
		apply_rotate(&m->camera, m->transformer, 180, 'z');
		create_new_image(m);
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (m->fade_alpha)
			m->fade_alpha = 0;
		else
			m->fade_alpha = 1;
		create_new_image(m);
	}
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		reset_cam(m);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		cycle_colorschemes(m);
}

void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_SUPER))
		translate_cam(m, 0, 0, (float)ydelta / 10.0);
	else
		translate_cam(m, 0, 0, ydelta);
}

void	handle_resize(int width, int height, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	m->window_h = height;
	m->window_w = width;
	m->canvas_h = height / 100.0;
	m->canvas_w = width / 100.0;
	create_new_image(m);
}