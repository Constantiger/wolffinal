/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:07:59 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 20:09:34 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	push_obj(t_sdl *sdl, int x, int y)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.45;
		sdl->obj[sdl->obj_count].size = 0.9;
		sdl->obj[sdl->obj_count].bord = 0.3;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].txtr = 0;
		sdl->obj[sdl->obj_count].iter = 1;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].proj = 0;
		sdl->obj[sdl->obj_count].enem = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_obj;
		sdl->obj_count++;
	}
}

void	push_score(t_sdl *sdl, int x, int y)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.25;
		sdl->obj[sdl->obj_count].size = 0.4;
		sdl->obj[sdl->obj_count].bord = 0.2;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].txtr = 8;
		sdl->obj[sdl->obj_count].iter = 0;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].proj = 0;
		sdl->obj[sdl->obj_count].enem = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_score;
		sdl->obj_count++;
	}
}

void	push_key(t_sdl *sdl, int x, int y)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.25;
		sdl->obj[sdl->obj_count].size = 0.4;
		sdl->obj[sdl->obj_count].bord = 0.2;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].txtr = 9;
		sdl->obj[sdl->obj_count].iter = 0;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_key;
		sdl->obj_count++;
	}
}

void	put_obj(t_sdl *sdl, int ind, int x, int size)
{
	int		i;
	int		j;
	int		color;
	int		y;

	i = 0;
	y = (WIN_H - size) / 2 + (atan((sdl->height -
	sdl->obj[ind].p.v[2]) / sdl->obj[ind].len)) / sdl->ang + sdl->y_ang_i;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((i + x) < 0 || (i + x) > sdl->size)
				break ;
			if (sdl->l[i + x].v[2] < sdl->obj[ind].len)
				break ;
			color = texturebmp(sdl, (float)i / size,
			(float)j / size, sdl->obj[ind].txtr);
			if ((color & 255) != 255)
				put_pixel(sdl, i + x + sdl->off, j + y, color);
			j++;
		}
		i++;
	}
}

void	draw_obj(void *s, int ind)
{
	int		l;
	float	size;
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	size = atan(sdl->obj[ind].size / sdl->obj[ind].len) / sdl->ang;
	l = xon_screen(sdl, set_v(sdl->obj[ind].p.v[0],
				sdl->obj[ind].p.v[1], sdl->obj[ind].p.v[2]));
	put_obj(sdl, ind, l - size / 2, size);
}
