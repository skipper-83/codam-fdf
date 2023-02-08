/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/05 22:42:43 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
# include "libft.h"
# include "fdf.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>

# define WIDTH 256
# define HEIGHT 256

typedef struct s_pixel{
	int	x;
	int	y;
	int	color;
}	t_pixel;

typedef struct s_line{
	int	longest;
	int	shortest;
	int	numerator;
	int	width;
	int	height;
	int	x_step1;
	int	y_step1;
	int	x_step2;
	int	y_step2;
}	t_line;

mlx_image_t	*g_img;

void	draw_line(t_pixel px1, t_pixel px2);

#endif