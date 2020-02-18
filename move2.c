/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:55:52 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 14:07:53 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	collx_cicle(t_sdl *s, float sign)
{
	int	i;

	i = -1;
	while (i < 2)
	{
		if (wallat(s, s->r.p.v[0] + sign, s->r.p.v[1] + i))
		{
			s->wa[i + 1].v[0] = (int)s->r.p.v[0] + sign + 0.5;
			s->wa[i + 1].v[1] = (int)s->r.p.v[1] + i + 0.5;
		}
		else
		{
			s->wa[i + 1].v[0] = -1.0;
			s->wa[i + 1].v[1] = -1.0;
		}
		i++;
	}
}

void	colly_cicle(t_sdl *s, float sign)
{
	int	i;

	i = -1;
	while (i < 2)
	{
		if (wallat(s, s->r.p.v[0] + i, s->r.p.v[1] + sign))
		{
			s->wa[i + 1].v[0] = (int)s->r.p.v[0] + i + 0.5;
			s->wa[i + 1].v[1] = (int)s->r.p.v[1] + sign + 0.5;
		}
		else
		{
			s->wa[i + 1].v[0] = -1.0;
			s->wa[i + 1].v[1] = -1.0;
		}
		i++;
	}
}

void	move(t_sdl *sdl)
{
	wall_coll(sdl);
}

void	set_speed(float sx, float sy, t_sdl *s)
{
	s->spdx += sx;
	s->spdy += sy;
}

void	jump_f(t_sdl *sdl)
{
	if (sdl->jump == 1)
	{
		if (sdl->height > 0.49)
		{
			sdl->height += sdl->spdz;
			sdl->spdz -= sdl->gforce;
		}
		else
		{
			sdl->jump = 0;
			sdl->height = 0.5;
			sdl->spdz = 0.0;
		}
	}
}
