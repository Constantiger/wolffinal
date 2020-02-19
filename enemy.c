/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:55:09 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 15:27:42 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	push_enemy(t_sdl *sdl, int x, int y)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.40;
		sdl->obj[sdl->obj_count].size = 0.9;
		sdl->obj[sdl->obj_count].bord = 0.5;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 10;
		sdl->obj[sdl->obj_count].txtr = 10;
		sdl->obj[sdl->obj_count].iter = 1;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].move = 0;
		sdl->obj[sdl->obj_count].atack = 0;
		sdl->obj[sdl->obj_count].see = 0;
		sdl->obj[sdl->obj_count].hp = 100;
		sdl->obj[sdl->obj_count].proj = 0;
		sdl->obj[sdl->obj_count].enem = 1;
		sdl->obj[sdl->obj_count].fram = 4;
		sdl->obj[sdl->obj_count].pl = sdl->obj[sdl->obj_count].p;
		sdl->obj[sdl->obj_count].draw_f = &draw_enemy;
		sdl->obj[sdl->obj_count].act_f = &act_obj;
		sdl->obj[sdl->obj_count].anim_f = &anim_enemy;
		sdl->obj_count++;
	}
}

void	coll_enemy_dx(t_sdl *sdl, float dx, int ind)
{
	int i;

	i = 0;
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].iter && i != ind)
		{
			if (detect(sdl->obj[ind].p, sdl->obj[ind].bord,
						sdl->obj[i].p, sdl->obj[i].bord))
				sdl->obj[ind].p.v[0] += 2 * dx;
		}
		i++;
	}
}

void	coll_enemy_dy(t_sdl *sdl, float dy, int ind)
{
	int i;

	i = 0;
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].iter && i != ind)
		{
			if (detect(sdl->obj[ind].p, sdl->obj[ind].bord,
						sdl->obj[i].p, sdl->obj[i].bord))
				sdl->obj[ind].p.v[1] += 2 * dy;
		}
		i++;
	}
}

void	coll_enemy(t_sdl *sdl, int ind)
{
	float	dx;
	float	dy;
	float	b;

	dx = (sdl->obj[ind].p.v[0] - sdl->obj[ind].pl.v[0]) * 0.021;
	dy = (sdl->obj[ind].p.v[1] - sdl->obj[ind].pl.v[1]) * 0.021;
	b = sdl->obj[ind].bord / 2;
	sdl->obj[ind].p.v[0] -= dx;
	if (wallat(sdl, sdl->obj[ind].p.v[0] - b, sdl->obj[ind].p.v[1] - b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] - b, sdl->obj[ind].p.v[1] + b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] + b, sdl->obj[ind].p.v[1] - b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] + b, sdl->obj[ind].p.v[1] + b))
		sdl->obj[ind].p.v[0] += dx;
	coll_enemy_dx(sdl, dx, ind);
	sdl->obj[ind].p.v[1] -= dy;
	if (wallat(sdl, sdl->obj[ind].p.v[0] - b, sdl->obj[ind].p.v[1] - b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] - b, sdl->obj[ind].p.v[1] + b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] + b, sdl->obj[ind].p.v[1] - b) ||
		wallat(sdl, sdl->obj[ind].p.v[0] + b, sdl->obj[ind].p.v[1] + b))
		sdl->obj[ind].p.v[1] += dy;
	coll_enemy_dy(sdl, dy, ind);
}

void	see_enemy(t_sdl *sdl, int ind)
{
	t_ray	r;
	t_vect	res;

	r.p = sdl->r.p;
	r.a_i = xon_screen(sdl, sdl->obj[ind].p) + sdl->x_ang_i - sdl->hsize;
	if (sdl->obj[ind].see)
		put_line(sdl, set_v(r.p.v[0] * sdl->bs + 25,
			r.p.v[1] * sdl->bs + 25, 0.0),
			set_v(r.p.v[0] * sdl->bs + 25 + cos(r.a_i * sdl->ang) * 100,
			r.p.v[1] * sdl->bs + 25 + sin(r.a_i * sdl->ang) * 100, 0.0),
			c(255, 0, 0));
	res = cast_ray(sdl, r);
	if (res.v[2] > sdl->obj[ind].len && sdl->obj[ind].len < 8.0)
	{
		sdl->obj[ind].see = 1;
		sdl->obj[ind].pl = sdl->r.p;
	}
	else
		sdl->obj[ind].see = 0;
}
