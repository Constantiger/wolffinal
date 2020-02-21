/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:41:56 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 16:21:39 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	next_map(t_sdl *sdl, char *file, int ind)
{
	int	i;
	int	k;

	i = ind - 2;
	k = 0;
	while (file[i] != 'E')
	{
		i--;
		k++;
	}
	i++;
	if (k == 0)
		sdl->has_next = 0;
	else
		sdl->has_next = 1;
	sdl->next_level[k] = '\0';
	k--;
	while (k >= 0 && k < 99)
	{
		sdl->next_level[k] = file[i + k];
		k--;
	}
}

int		valid_map(t_sdl *s)
{
	int	i;
	int	j;

	if (s->msx < 3 || s->msy < 3)
		return (4);
	i = 0;
	j = 0;
	while (j < s->msy)
	{
		while (i < s->msx)
		{
			if ((i == 0 || i == (s->msx - 1)) && s->m[i][j] != '1')
				return (2);
			if ((j == 0 || j == (s->msy - 1)) && s->m[i][j] != '1')
				return (3);
			i++;
		}
		j++;
		i = 0;
	}
	return (1);
}

int		modd(float a, float b)
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	return (a > b);
}

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

t_box	set_b(int x, int y, int size)
{
	t_box	b;

	b.x = x;
	b.y = y;
	b.size = size;
	return (b);
}
