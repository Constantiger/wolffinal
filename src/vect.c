/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 20:04:57 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 17:15:01 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_vect	set_v(float x, float y, float z)
{
	t_vect	v;

	v.v[0] = x;
	v.v[1] = y;
	v.v[2] = z;
	return (v);
}

void	set_vc(t_vect *v, float x, float y, int c)
{
	v->v[0] = x;
	v->v[1] = y;
	v->c = c;
}

void	vect_len(t_sdl *sdl, t_vect *res)
{
	float	t;
	float	t2;

	t = sdl->r.p.v[0] - res->v[0];
	t2 = sdl->r.p.v[1] - res->v[1];
	res->v[2] = t * t + t2 * t2;
}
