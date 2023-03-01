/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:24 by albertvanan       #+#    #+#             */
/*   Updated: 2023/03/01 12:46:12 by avan-and         ###   ########.fr       */
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
# include <errno.h>

# define WINDOW_NAME "FDF"
# define WIDTH 1200
# define HEIGHT 800
# define MARGIN 60

# define DEFAULT_COLOR 0xFFFFFFFF

# define HEX_BASE "0123456789abcdef"
# define Z 0
# define COLOR 1
# define KEEP_M1 0
# define FREE_M1 1
# define PERSPECTIVE 0
# define PARALLEL 1
# define CHROME 0
# define NO_CHROME 1

typedef struct s_angle
{
	float	x;
	float	y;
	float	z;
}	t_angle;

typedef int	(*t_color_scheme)(float z);

typedef struct s_meta{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_list			*points;
	char			**line_arr;
	char			**point_arr;
	int				drawing_h;
	int				drawing_w;
	int				drawing_d;
	int				window_w;
	int				window_h;
	float			canvas_w;
	float			canvas_h;
	int				total_px;
	int				max_z;
	int				min_z;
	char			projection;
	char			*filename;
	float			**world;
	float			**camera;
	float			**transformer;
	int				mouse_x;
	int				mouse_y;
	t_angle			cam_rotation;
	t_angle			world_rotation;
	char			fade_alpha;
	t_color_scheme	color_scheme;
	char			is_rendered;
	t_list			*strings;
	mlx_image_t		*rotations[2];
	char			chrome;
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

//	FUNCTIONS WITH THEIR OWN FILE

void	draw_line(t_meta *m, mlx_image_t *img, t_pixel px1, t_pixel px2);
void	parse_file(t_meta *m);
float	**m44_invert(float **input, t_meta *m);

// UTIL

void	free_array(char **arr);
void	exit_error(char *error_msg, t_meta *m);
void	*exit_on_null(void *ptr, t_meta *m44_init);
void	free_meta(t_meta *m);
void	free_strings_list(t_list **list, t_meta *m);

// MATRIX TRANSFORMATIONS

void	m44_rotate(float **matrix, float angle, char axis);
void	m44_scale(float **matrix, float x, float y, float z);
void	m44_translate(float **matrix, float x, float y, float z);
float	ft_rad(float angle);

// DRAW FUNCTIONS

void	put_pixel_safe(t_meta *m, mlx_image_t *img, t_pixel pixel);
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

// COLOR

int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		get_alpha(int color);
int		make_color(int r, int g, int b, int a);

// FDF UTIL

void	create_new_image(t_meta *m);
t_meta	*init_meta(char *filename);

// DEBUG

void	print_meta(t_meta *m);
void	print_point(void *param);
void	m44_print(float **matrix);
float	**m44_arr_to_pointer(float matrix[][4]);

// WORLD TRANSFORMATONS

void	rotate_world(t_meta *m, float angle, char axis);
void	scale_world(t_meta *m, float x, float y, float z);
void	translate_world(t_meta *m, float x, float y, float z);
void	expand_world(t_meta *m, float z);

// CAMERA TRANSFORMATIONS

void	update_rotation_var(t_angle *r_var, float angle, char axis);
void	apply_rotate(float ***target, float **rotator, float angle, char axis);
void	translate_cam(t_meta *m, float x, float y, float z);
void	rotate_cam(t_meta *m, float angle, char axis);
void	reset_cam(t_meta *m);

// HOOKS

void	handle_key(mlx_key_data_t keydata, void *param);
void	handle_scroll(double xdelta, double ydelta, void *param);
void	handle_resize(int width, int height, void *param);

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t mod, void *prm);
void	frame_hook(void *param);

// COLOR SCHEMES

int		weird_purple_colors(float z);
int		minecraft_colors(float z);
int		atlas_colors(float z);
int		rainbow(float z);

// COLOR SCHEME UTILS

void	fade_alpha_with_z(t_point p, t_pixel *px);
void	cycle_colorschemes(t_meta *m);
void	apply_color_scheme(t_meta *m, int (*scheme)(float z));

// CHROME

void	update_rotation_disp(t_meta *m);
void	draw_chrome(t_meta *m);
void	remove_chrome(t_meta *m);

#endif