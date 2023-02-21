/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:41:20 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/21 23:24:37 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	has_digits(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}


static void	add_point(t_meta *m, int x, int y, char **point_arr)
{
	t_list	*new;
	t_point	*point;

	point = exit_on_null(malloc(sizeof(t_point)));
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

	line_arr = exit_on_null(ft_split(line, ' '));
	i = 0;
	while (line_arr[i] && line_arr[i][0] != '\n')
	{
		point_arr = exit_on_null(ft_split(line_arr[i], ','));
		if (!has_digits(point_arr[Z]))
			exit_error(ERROR_MAP_NUMBERS);
		add_point(m, i + 1, y, point_arr);
		free_array(point_arr);
		i++;
	}
	if (m->drawing_w == 0)
		m->drawing_w = i;
	if (m->drawing_w != i)
		exit_error(ERROR_MAP_SQUARE);
	free_array(line_arr);
}

// float	map_coeff(float x, float in_min, float in_max)
// {
// 	return ((x - in_min) / (in_max - in_min));
// }

// void	rotate_cam(t_meta *m, float angle, char axis);

int	weird_purple_colors(float z)
{
	if (z > 100)
		return (0xFFDF8DFF);
	if (z > 75)
		return (0xFFDE7AFF);
	if (z > 50)
		return (0xFFC568FF);
	if (z > 25)
		return (0xFD996BFF);
	if (z > 15)
		return (0xF7856CFF);
	if (z > 10)
		return (0xF06E6CFF);
	if (z > 5)
		return (0xD9576BFF);
	if (z > 0)
		return (0xA44369FF);
	if (z > -10)
		return (0x833F68FF);
	if (z > -20)
		return (0x833F68FF);
	if (z > -50)
		return (0x5E3C65FF);
	return (0x3F3A63FF);
}

int	minecraft_colors(float z)
{
	if (z > 70)
		return (0xE9EAF0FF);
	if (z > 62)
		return (0xC4C1BDFF);
	if (z > 50)
		return (0x4C591AFF);
	if (z > 10)
		return (0x4C591AFF);
	if (z > 1)
		return (0x4D5E36FF);
	if (z > 0)
		return (0xD8D19CFF);
	if (z > -5)
		return (0x444CC6FF);
	if (z > -10)
		return (0x2A2EAEFF);
	if (z > -30)
		return (0x3D497CFF);
	return (0x05093dFF);
}

void	apply_color_scheme(t_meta *m, int (*scheme)(float z))
{
	t_list	*head;
	t_point	*point;

	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		point->color = scheme(point->z);
		head = head->next;
	}
}

void	spread_drawing(t_meta *m)
{
	t_list		*head;
	t_point		*point;
	float		coeff;

	coeff = 5 + (m->drawing_d / m->drawing_w);
	m44_scale(m->transformer, coeff, coeff, 1);
	m44_translate(m->transformer, -((m->drawing_w * coeff) / 2) - 1, \
									-((m->drawing_h * coeff) / 2) - 1, 0);
	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		m44_multiply_point(m->transformer, point);
		head = head->next;
	}
	coeff = m->drawing_w;
	if (m->drawing_d * .3 > m->drawing_w)
		coeff = m->drawing_d * .3;
	apply_rotate(&m->camera, m->transformer, 180, 'x');
	apply_rotate(&m->camera, m->transformer, 135, 'z');
	m44_translate(m->camera, 0, 0, (coeff) * 1.8);
	// apply_color_scheme(m, weird_purple_colors);
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
	spread_drawing(m);
}
