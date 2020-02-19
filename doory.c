/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doory.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 19:20:27 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:28:04 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	push_doory_help(t_sdl *sdl, int x, int y)
{
	if (sdl->doory_count < 100)
	{
		sdl->doory[sdl->doory_count].v[0] = x + 0.5;
		sdl->doory[sdl->doory_count].v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].act_f = &act_doory;
		sdl->doory_count++;
	}
}

void	push_doory(t_sdl *sdl, int x, int y)
{
	push_doory_help(sdl, x, y);
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.45;
		sdl->obj[sdl->obj_count].size = 0.9;
		sdl->obj[sdl->obj_count].bord = 0.5;
		sdl->obj[sdl->obj_count].dr = 0;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].iter = 1;
		if (islock(sdl, x, y))
			sdl->obj[sdl->obj_count].lock = 1;
		else
			sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].ind = sdl->doory_count - 1;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].anim_f = &anim_doory;
		sdl->obj_count++;
	}
}

t_vect	cast_doory1(t_sdl *sdl, float t, int i)
{
	t_vect	res;
	float	dy;
	float	d;

	if ((t > -0.00001 && t < 0.00001))
		return (set_v(100.0, 100.0, 0.0));
	t = 1 / t;
	d = (int)sdl->r.p.v[1] - sdl->doory[i].v[1];
	dy = sdl->r.p.v[1] - (int)sdl->r.p.v[1];
	res.v[0] = sdl->r.p.v[0] - t * dy - d * t;
	res.v[1] = sdl->doory[i].v[1];
	t = res.v[0] - sdl->r.p.v[0];
	d = res.v[1] - sdl->r.p.v[1];
	res.v[2] = sqrt(t * t + d * d);
	return (res);
}

void	set_paramy(t_sdl *sdl, int *l1, int *l2, int ind)
{
	*l1 = xon_screen(sdl, set_v(sdl->doory[ind].v[0] - 0.5,
				sdl->doory[ind].v[1], sdl->doory[ind].v[2]));
	*l2 = xon_screen(sdl, set_v(sdl->doory[ind].v[0] + 0.5,
				sdl->doory[ind].v[1], sdl->doory[ind].v[2]));
}

void	draw_doory(t_sdl *sdl, int ind)
{
	int		l1;
	int		l2;
	int		i;
	t_vect	len2;

	set_paramy(sdl, &l1, &l2, ind);
	if (l2 < l1)
		swapi(&l1, &l2);
	if (l2 - l1 > 1900)
		return ;
	if (l1 < 0)
		i = 0;
	else
		i = l1;
	while (i < l2 && i++ < sdl->size)
	{
		len2 = cast_doory1(sdl, sdl->tang[sdl->ar[i].a_i], ind);
		if (sdl->l[i].v[2] > len2.v[2])
		{
			sdl->l[i].v[0] = len2.v[0];
			sdl->l[i].v[1] = len2.v[1];
			sdl->l[i].v[2] = len2.v[2];
			draw_doors(sdl, l1, l2, i);
		}
	}
}
