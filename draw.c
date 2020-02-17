/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:16:03 by aannara           #+#    #+#             */
/*   Updated: 2020/01/29 15:23:30 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		c(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) + (g << 8) + b);
}

void	put_pixel(t_sdl *sdl, int x, int y, int color)
{
	unsigned int	col;

	col = color;
	if (x < 0 || x > WIN_L || y < 0 || y > WIN_H - 1)
		return ;
	sdl->img[y * WIN_L + x] = col;
}

void	put_lx(t_sdl *sdl, t_vect p1, t_vect d, int color)
{
	int	i;

	i = 0;
	while (i < d.v[0])
	{
		put_pixel(sdl, i + p1.v[0], (float)i / d.v[0] * d.v[1] +
				p1.v[1], color);
		i++;
	}
}

void	put_ly(t_sdl *sdl, t_vect p1, t_vect d, int color)
{
	int	i;

	i = 0;
	while (i < d.v[1])
	{
		put_pixel(sdl, (float)i / d.v[1] * d.v[0] + p1.v[0],
				i + p1.v[1], color);
		i++;
	}
}

int		modd(float a, float b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	return (a > b);
}

void	put_line(t_sdl *sdl, t_vect p1, t_vect p2, int color)
{
	t_vect	d;
	float	temp;

	d.v[0] = p2.v[0] - p1.v[0];
	d.v[1] = p2.v[1] - p1.v[1];
	if (modd(d.v[0], d.v[1]))
	{
		if (d.v[0] < 0)
		{
			p1 = p2;
			d.v[0] = -d.v[0];
			d.v[1] = -d.v[1];
		}
		put_lx(sdl, p1, d, color);
	}
	else
	{
		if (d.v[1] < 1)
		{
			p1 = p2;
			d.v[0] = -d.v[0];
			d.v[1] = -d.v[1];
		}
		put_ly(sdl, p1, d, color);
	}
}

void	put_box(t_sdl *sdl, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		while (i < size)
		{
			put_pixel(sdl, i + x, j + y, color);
			i++;
		}
		j++;
		i = 0;
	}
}
