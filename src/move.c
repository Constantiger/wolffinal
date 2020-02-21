/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:46:29 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 14:07:49 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	detect(t_vect a, float s1, t_vect b, float s2)
{
	float	s11;
	float	s22;

	s11 = s1 / 2;
	s22 = s2 / 2;
	return (((a.v[0] + s11) > (b.v[0] - s22)) &&
			((a.v[0] - s11) < (b.v[0] + s22)) &&
			((a.v[1] + s11) > (b.v[1] - s22)) &&
			((a.v[1] - s11) < (b.v[1] + s22)));
}

void	collx(t_sdl *s, float sx)
{
	int		i;
	float	sign;

	if (sx > 0)
		sign = 1.0;
	else
		sign = -1.0;
	s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1];
	collx_cicle(s, sign);
	i = 0;
	while (i < 3)
	{
		if (detect(s->p, s->bord, s->wa[i], 1.0))
		{
			s->spdx = 0.0;
			s->p.v[0] = s->r.p.v[0];
			return ;
		}
		i++;
	}
	s->p.v[0] = s->r.p.v[0];
}

void	colly(t_sdl *s, float sy)
{
	int		i;
	float	sign;

	if (sy > 0)
		sign = 1.0;
	else
		sign = -1.0;
	s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1] + s->spdy * s->spd;
	colly_cicle(s, sign);
	i = 0;
	while (i < 3)
	{
		if (detect(s->p, s->bord, s->wa[i], 1.0))
		{
			s->spdy = 0.0;
			s->p.v[1] = s->r.p.v[1];
			return ;
		}
		i++;
	}
}

void	coll(t_sdl *s, t_vect obj, float obj_bord)
{
	s->p = s->r.p;
	s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
	s->p.v[1] = s->r.p.v[1] + s->spdy * s->spd;
	if (detect(s->p, s->bord, obj, obj_bord))
	{
		s->p = s->r.p;
		s->p.v[0] = s->r.p.v[0] + s->spdx * s->spd;
		if (detect(s->p, s->bord, obj, obj_bord))
		{
			if (s->spdx > 0)
				s->p.v[0] = obj.v[0] - (obj_bord + s->bord) / 2 - 0.01;
			else
				s->p.v[0] = obj.v[0] + (obj_bord + s->bord) / 2 + 0.01;
			s->spdx = 0;
		}
		s->p.v[1] = s->r.p.v[1] + s->spdy * s->spd;
		if (detect(s->p, s->bord, obj, obj_bord))
		{
			if (s->spdy > 0)
				s->p.v[1] = obj.v[1] - (obj_bord + s->bord) / 2 - 0.01;
			else
				s->p.v[1] = obj.v[1] + (obj_bord + s->bord) / 2 + 0.01;
			s->spdy = 0;
		}
	}
}

void	wall_coll(t_sdl *s)
{
	float	sx;
	float	sy;
	int		i;

	i = 0;
	sx = s->spd * s->spdx;
	sy = s->spd * s->spdy;
	collx(s, sx);
	colly(s, sy);
	while (i < s->obj_count)
	{
		if (s->obj[i].iter)
			coll(s, s->obj[i].p, s->obj[i].bord);
		i++;
	}
	s->r.p = s->p;
	s->spdx = 0.0;
	s->spdy = 0.0;
}
