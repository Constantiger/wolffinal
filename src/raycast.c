/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:54:50 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 17:14:57 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_vect	cast_x1(t_sdl *sdl, t_ray r, float t)
{
	t_vect	res;
	float	dx;
	int		i;

	i = 1;
	dx = r.p.v[0] - (int)r.p.v[0];
	res.v[1] = r.p.v[1] + t * (1.0 - dx);
	res.v[0] = (int)r.p.v[0] + 1.0;
	if (check(&res))
		return (res);
	while ((res.v[0] > 0.0) && (res.v[0] < sdl->msx)
			&& (res.v[1] < sdl->msy) && (res.v[1] > 0.0)
			&& iswall(sdl, (int)res.v[0], (int)res.v[1]))
	{
		res.v[1] = r.p.v[1] + t * (1.0 - dx + i);
		res.v[0] = (int)r.p.v[0] + 1.0 + i;
		i++;
	}
	return (res);
}

t_vect	cast_x2(t_sdl *sdl, t_ray r, float t)
{
	t_vect	res;
	float	dx;
	int		i;

	i = 1;
	dx = r.p.v[0] - (int)r.p.v[0];
	res.v[1] = r.p.v[1] - t * dx;
	res.v[0] = (int)r.p.v[0];
	if (check(&res))
		return (res);
	while ((res.v[0] > 0.0) && (res.v[0] < sdl->msx)
			&& (res.v[1] < sdl->msy) && (res.v[1] > 0.0)
			&& iswall(sdl, (int)res.v[0] - 1, (int)res.v[1]))
	{
		res.v[1] = r.p.v[1] - t * dx - t * i;
		res.v[0] = (int)r.p.v[0] - i;
		i++;
	}
	return (res);
}

t_vect	cast_y1(t_sdl *sdl, t_ray r, float t)
{
	t_vect	res;
	float	dy;
	int		i;

	if (t > -0.001 && t < 0.001)
		return (set_v(100.0, 100.0, 0.0));
	t = 1 / t;
	i = 1;
	dy = r.p.v[1] - (int)r.p.v[1];
	res.v[1] = (int)r.p.v[1];
	res.v[0] = r.p.v[0] - t * dy;
	if (check(&res))
		return (res);
	while ((res.v[1] > 0.0) && (res.v[1] < sdl->msy)
			&& (res.v[0] < sdl->msx) && (res.v[0] > 0.0)
			&& iswall(sdl, (int)res.v[0], (int)res.v[1] - 1))
	{
		res.v[1] = (int)r.p.v[1] - i;
		res.v[0] = r.p.v[0] - t * dy - t * i;
		i++;
	}
	return (res);
}

t_vect	cast_y2(t_sdl *sdl, t_ray r, float t)
{
	t_vect	res;
	float	dy;
	int		i;

	if (t > -0.001 && t < 0.001)
		return (set_v(100.0, 100.0, 0.0));
	t = 1 / t;
	i = 1;
	dy = r.p.v[1] - (int)r.p.v[1];
	res.v[0] = r.p.v[0] + t * (1.0 - dy);
	res.v[1] = (int)r.p.v[1] + 1.0;
	if (check(&res))
		return (res);
	while ((res.v[1] > 0.0) && (res.v[1] < sdl->msy)
			&& (res.v[0] < sdl->msx) && (res.v[0] > 0.0)
			&& iswall(sdl, (int)res.v[0], (int)res.v[1]))
	{
		res.v[0] = r.p.v[0] + t * (1.0 - dy + i);
		res.v[1] = (int)r.p.v[1] + 1.0 + i;
		i++;
	}
	return (res);
}

t_vect	cast_ray(t_sdl *sdl, t_ray r)
{
	t_vect	resx;
	t_vect	resy;
	float	t;

	t = sdl->tang[r.a_i];
	if (r.a_i <= sdl->hpi || r.a_i >= sdl->pihpi)
		resx = cast_x1(sdl, r, t);
	else
		resx = cast_x2(sdl, r, t);
	if (r.a_i >= sdl->pi)
		resy = cast_y1(sdl, r, t);
	else
		resy = cast_y2(sdl, r, t);
	vect_len(sdl, &resx);
	vect_len(sdl, &resy);
	if (resx.v[2] < resy.v[2])
	{
		resx.v[2] = sqrt(resx.v[2]);
		resx.c = 1;
		return (resx);
	}
	resy.c = 0;
	resy.v[2] = sqrt(resy.v[2]);
	return (resy);
}
