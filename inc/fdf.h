/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/20 23:58:38 by albertvanan      ###   ########.fr       */
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
# define WIDTH 1024
# define HEIGHT 768
# define MARGIN 60
# define CANVAS_H 10
# define CANVAS_W 7.68

# define DEFAULT_COLOR 0xFFFFFFFF

# define HEX_BASE "0123456789abcdef"
# define Z 0
# define COLOR 1
# define KEEP_M1 0
# define FREE_M1 1
# define PERSPECTIVE 0
# define PARALLEL 1

typedef struct s_meta{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*points;
	int			drawing_h;
	int			drawing_w;
	int			drawing_d;
	int			total_px;
	int			max_z;
	int			min_z;
	char		projection;
	char		*filename;
	float		**world;
	float		**camera;
	float		**transformer;
}	t_meta;

typedef struct s_pixel{
	int		x;
	int		y;
	int		color;
	char	enabled;
}	t_pixel;

typedef struct s_point{
	float		x;
	float		y;
	float		z;
	int			color;
	t_meta		*m;
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

typedef struct s_angle
{
	float	x;
	float	y;
	float	z;
}	t_angle;

void	draw_line(mlx_image_t *img, t_pixel px1, t_pixel px2);
void	parse_file(t_meta *m);
void	free_array(char **arr);
void	exit_error(char *error_msg);
float	**m44_invert(float **input);

// MATRIX TRANSFORMATIONS

void	m44_rotate(float **matrix, float angle, char axis);
void	m44_scale(float **matrix, float x, float y, float z);
void	m44_translate(float **matrix, float x, float y, float z);
float	ft_rad(float angle);

// DRAW FUNCTIONS

void	put_pixel_safe(mlx_image_t *img, t_pixel pixel);
void	draw_raster(t_pixel *map, t_meta *m, mlx_image_t *img);
void	draw_pixels(t_pixel *pixel, t_meta *m, mlx_image_t *img);

// MATRIX UTILS

float	**m44_init(void);
void	m44_free(float **matrix);
float	**m44_copy(float **matrix);
float	**m44_dot_product(float **m1, float **m2, int free_m1);
void	m44_to_identity_matrix(float **matrix);
// int		m44_is_identity_matrix(float **matrix);

// POINT UTILS

void	m44_multiply_point(float **m, t_point *p);
t_pixel	*points_to_pixels(t_meta *m);
t_pixel	point_to_pixel(t_point *point, t_meta *m);

// DEBUG

void	print_meta(t_meta *m);
void	print_point(void *param);
void	m44_print(float **matrix);
float	**m44_arr_to_pointer(float matrix[][4]);

#endif