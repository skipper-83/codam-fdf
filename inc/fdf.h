/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/13 22:39:34 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42.h"
# include "libft.h"
# include "errors.h"
# include <fcntl.h> // for open
# include <stdio.h>  // for read
# include <string.h> // for perror
# include <math.h>

# define WINDOW_NAME "FDF"
# define WIDTH 600
# define HEIGHT 600
# define MARGIN 60

# define DEFAULT_COLOR 0xFFFFFFFF

# define HEX_BASE "0123456789abcdef"
# define Z 0
# define COLOR 1
# define KEEP_M1 0
# define FREE_M1 1

typedef struct s_meta{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*points;
	int			drawing_h;
	int			drawing_w;
	int			drawing_d;
	int			max_z;
	int			min_z;
	char		*filename;
}	t_meta;

typedef struct s_pixel{
	int	x;
	int	y;
	int	color;
}	t_pixel;

typedef struct s_point{
	float		x;
	float		y;
	float		z;
	int		color;
	t_meta	*m;
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

void	draw_line(mlx_image_t *img, t_pixel px1, t_pixel px2);
void	parse_file(t_meta *m);
void	free_array(char **arr);
void	exit_error(char *error_msg);
float	**matrix4x4_invert(float **input);

// MATRIX UTILS

float	**matrix4x4_init(void);
void	matrix4x4_free(float **matrix);
float	**matrix4x4_copy(float **matrix);
float	**matrix4x4_dot_product(float **m1, float **m2, int free_m1);
void	matrix4x4_multiply_point(float **m, t_point *p);

// DEBUG

void	print_meta(t_meta *m);
void	print_point(void *param);
void	matrix4x4_print(float **matrix);
float	**matrix4x4_arr_to_pointer(float matrix[][4]);

#endif