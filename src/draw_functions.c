/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:22 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/23 00:23:04 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Put pixel if it is within the boundaries of the screen
 * 
 * @param m 
 * @param img 
 * @param pixel 
 */
void	put_pixel_safe(t_meta *m, mlx_image_t *img, t_pixel pixel)
{
	if (!pixel.enabled)
		return ;
	if (pixel.x >= 0 && pixel.x < m->window_w)
		if (pixel.y >= 0 && pixel.y < m->window_h)
			mlx_put_pixel(img, pixel.x, pixel.y, pixel.color);
}

/**
 * @brief Draw lines between the points in [map]
 * 
 * @param map 
 * @param m 
 * @param img 
 */
void	draw_raster(t_pixel *map, t_meta *m, mlx_image_t *img)
{
	int	rows;
	int	cols;
	int	i;

	rows = 0;
	cols = 0;
	i = 0;
	while (rows < m->drawing_h)
	{
		while (cols < m->drawing_w)
		{
			if (cols < m->drawing_w - 1)
				draw_line(m, img, map[i], map[i + 1]);
			if (rows < m->drawing_h - 1)
				draw_line(m, img, map[i], map[i + m->drawing_w]);
			i++;
			cols++;
		}
		cols = 0;
		rows++;
	}
}

/**
 * @brief Draw the pixels in [map]
 * 
 * @param pixel 
 * @param m 
 * @param img 
 */
void	draw_pixels(t_pixel *pixel, t_meta *m, mlx_image_t *img)
{
	int	i;

	i = 0;
	while (i < m->total_px)
	{
		put_pixel_safe(m, img, pixel[i]);
		i++;
	}
}
