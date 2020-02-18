/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:07:59 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 16:14:09 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		wallat(t_sdl *s, float x, float y)
{
	return (s->m[(int)x][(int)y] == '1');
}

int		partition(t_sdl *s, int low, int high)
{
	t_obj	pivor;
	t_obj	temp;
	int		i;
	int		j;

	pivor = s->obj[high];
	i = (low - 1);
	j = low;
	while (j <= (high - 1))
	{
		if (s->obj[j].len < pivor.len)
		{
			i++;
			temp = s->obj[j];
			s->obj[j] = s->obj[i];
			s->obj[i] = temp;
		}
		j++;
	}
	temp = s->obj[i + 1];
	s->obj[i + 1] = s->obj[high];
	s->obj[high] = temp;
	return (i + 1);
}

void	qwsort(t_sdl *s, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(s, low, high);
		qwsort(s, low, pi - 1);
		qwsort(s, pi + 1, high);
	}
}

void	remove_obj(t_sdl *sdl)
{
	int	i;

	i = sdl->obj_count - 1;
	while (i >= 0)
	{
		if (sdl->obj[i].p.v[0] > 100.0)
			sdl->obj_count--;
		i--;
	}
}

void	obj_len(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->obj_count)
	{
		sdl->obj[i].len = leng(sdl->r.p, sdl->obj[i].p);
		i++;
	}
	qwsort(sdl, 0, sdl->obj_count - 1);
	remove_obj(sdl);
}
