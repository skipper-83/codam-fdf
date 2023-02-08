/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/08 13:41:42 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
# include "libft.h"
# include "fdf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 256
# define HEIGHT 256

typedef struct s_pixel{
	int	x;
	int	y;
	int	color;
}	t_pixel;

typedef struct s_point{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

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

typedef struct s_meta{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_meta;

void	draw_line(mlx_image_t *img, t_pixel px1, t_pixel px2);

#endif