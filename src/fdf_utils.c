/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:43:16 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 15:46:00 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initialize the metada struct
 * 
 * @param filename 
 * @return t_meta* 
 */
t_meta	*init_meta(char *filename)
{
	t_meta	*m;

	m = exit_on_null(ft_calloc(1, sizeof(t_meta)), NULL);
	m->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_NAME, true);
	if (m->mlx == NULL)
		exit_error(ERROR_MLX, m);
	m->filename = filename;
	m->max_z = INT32_MIN;
	m->min_z = INT32_MAX;
	m->world = exit_on_null(m44_init(), m);
	m->camera = exit_on_null(m44_init(), m);
	m->transformer = exit_on_null(m44_init(), m);
	m->window_w = WIDTH;
	m->window_h = HEIGHT;
	m->canvas_w = m->window_w / 100.0;
	m->canvas_h = m->window_h / 100.0;
	ft_printf("canvas h: %f\n", m->canvas_h);
	return (m);
}

/**
 * @brief Redraw image based on (changed) metadata [m] info
 * 
 * @param m 
 */
void	create_new_image(t_meta *m)
{
	t_list		*head;
	t_pixel		*map;
	t_point		*point;
	mlx_image_t	*new;

	new = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	map = points_to_pixels(m);
	draw_pixels(map, m, new);
	draw_raster(map, m, new);
	mlx_image_to_window(m->mlx, new, 0, 0);
	mlx_delete_image(m->mlx, m->img);
	free(map);
	m->img = new;
}
