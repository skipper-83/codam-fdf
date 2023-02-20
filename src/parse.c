/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:41:20 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/20 02:37:19 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_point(t_meta *m, int x, int y, char **point_arr)
{
	t_list	*new;
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (point == NULL)
		exit_error(ERROR_MEM);
	point->x = x;
	point->y = y;
	point->z = ft_atoi(point_arr[Z]);
	if (point_arr[COLOR])
	{
		point->color = (int)ft_atou_base(point_arr[COLOR], HEX_BASE, "0x");
		point->color = (point->color << 8) + 0xFF;
	}
	else
		point->color = DEFAULT_COLOR;
	if (point->z > m->max_z)
		m->max_z = point->z;
	if (point->z < m->min_z)
		m->min_z = point->z;
	point->m = m;
	new = ft_lstnew(point);
	if (new == NULL)
		exit_error(ERROR_MEM);
	ft_lstadd_front(&(m->points), new);
}

static void	parse_line(char *line, int y, t_meta *m)
{
	char		**line_arr;
	char		**point_arr;
	int			i;

	line_arr = ft_split(line, ' ');
	if (line_arr == NULL)
		exit_error(ERROR_MEM);
	i = 0;
	while (line_arr[i] && line_arr[i][0] != '\n')
	{
		point_arr = ft_split(line_arr[i], ',');
		add_point(m, i + 1, y, point_arr);
		free_array(point_arr);
		i++;
	}
	if (m->drawing_w == 0)
		m->drawing_w = i;
	if (m->drawing_w != i)
		exit_error(ERROR_MAP);
	free_array(line_arr);
}

float map_coeff(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void	spread_drawing(t_meta *m)
{
	// float		multiplier;
	// int			drawing_longest;
	// int			screen_shortest;
	t_list		*head;
	t_point		*point;
	float		**preset;
	float		coeff;

	preset = m44_init();
	if (preset == NULL)
		exit_error(ERROR_MEM);
	
	coeff = 5;
	// m44_scale(translate, ((float)m->drawing_w / CANVAS_W) / 10, ((float)m->drawing_w / CANVAS_W) / 10, 1);
	m44_scale(preset, coeff, coeff, 1);
	m44_translate(preset, -((m->drawing_w * coeff) / 2) - 1, -((m->drawing_h * coeff) / 2) - 1, 0);
	// drawing_longest = m->drawing_w;
	// if (m->drawing_h > drawing_longest)
	// 	drawing_longest = m->drawing_h;
	// screen_shortest = HEIGHT;
	// if (WIDTH < screen_shortest)
	// 	screen_shortest = HEIGHT;
	// multiplier = (float)(screen_shortest - (MARGIN * 2)) / (float)(drawing_longest - 1);
	// // ft_printf("multiplier is %f\n", multiplier);
	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		// point->y = (CANVAS_H / 2) - point->y;
		// point->z = ((CANVAS_H / 2) - point->z / 2) ;//- m->drawing_d / 10;
		point->z = -1 * map_coeff(point->z, m->min_z, m->max_z, 0, 1) * m->drawing_d;
		// point->z = -1 * ((CANVAS_H / m->drawing_d) * point->z);
		// point->z = 50 * ((m->drawing_w / m->drawing_d) * point->z);
		m44_multiply_point(preset, point);
		// ft_printf("point: %f, %f, %f\n", point->x, point->y, point->z);
		// point->z = map_coeff(point->z, m->min_z, m->max_z, 0.5, 1.5);
		// point->x = (point->x - 1) * multiplier + MARGIN;
		// point->y = (point->y - 1) * multiplier + MARGIN;
		head = head->next;
	}
	coeff = m->drawing_w;
	if (m->drawing_d * .3 > m->drawing_w)
		coeff = m->drawing_d * .3;
	m44_translate(m->camera, 0, 0, -(coeff));
	m44_rotate(m->camera, -45, 'z');
	m44_free(preset);
}

void	parse_file(t_meta *m)
{
	int		fd;
	int		y;
	char	*line;

	y = 0;
	fd = open(m->filename, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, y + 1, m);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	m->drawing_h = y;
	m->drawing_d = m->max_z - m->min_z;
	m->total_px = m->drawing_h * m->drawing_w;
	// ft_printf("drawing height / screen height: %f\n", ((float)m->drawing_h / CANVAS_H) / 10);
	ft_printf("drawing width / screen width: %f\n", WIDTH / (float)m->drawing_w);
	spread_drawing(m);
}
