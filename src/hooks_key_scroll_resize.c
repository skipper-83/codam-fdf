/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_key_scroll_resize.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:53:51 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/26 14:29:20 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_key2(mlx_key_data_t keydata, t_meta *m)
{
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		reset_cam(m);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		cycle_colorschemes(m);
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
	{
		if (m->chrome == CHROME)
			remove_chrome(m);
		else
			draw_chrome(m);
	}
}

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
	handle_key2(keydata, m);
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
	m->canvas_w = width / 100.0;
	m->canvas_h = height / 100.0;
	if (m->chrome == CHROME)
	{
		remove_chrome(m);
		draw_chrome(m);
	}
	create_new_image(m);
}
