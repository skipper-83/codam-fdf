/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:43:16 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/24 23:50:01 by albertvanan      ###   ########.fr       */
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
	m->canvas_w = m->window_w / 200.0;
	m->canvas_h = m->window_h / 200.0;
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

	new = mlx_new_image(m->mlx, m->window_w, m->window_h);
	if (new == NULL)
		exit_error(ERROR_MLX, m);
	map = points_to_pixels(m);
	draw_pixels(map, m, new);
	draw_raster(map, m, new);
	mlx_image_to_window(m->mlx, new, 0, 0);
	mlx_set_instance_depth(&new->instances[0], -1);
	if (m->chrome == CHROME)
		update_rotation_disp(m);
	if (m->img)
		mlx_delete_image(m->mlx, m->img);
	free(map);
	m->img = new;
}
