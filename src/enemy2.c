/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:16:38 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 15:23:23 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	damage_enemy(t_sdl *sdl, int ind)
{
	sdl->obj[ind].hp -= 30;
	sdl->obj[ind].see = 1;
	if (sdl->obj[ind].hp <= 0 && sdl->obj[ind].anim != 119)
	{
		sdl->obj[ind].size = 1.1;
		sdl->obj[ind].move = 0;
		sdl->obj[ind].see = 0;
		sdl->obj[ind].atack = 0;
		sdl->obj[ind].anim = 1;
		sdl->obj[ind].txtr = 14;
		sdl->obj[ind].iter = 0;
		sdl->obj[ind].enem = 0;
		sdl->obj[ind].anim_f = &death_enemy;
	}
}

void	death_enemy(void *s, int ind)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[ind].anim == 119)
		return ;
	if (sdl->obj[ind].anim > 0)
	{
		sdl->obj[ind].anim++;
	}
}

void	anim_enemy(void *s, int ind)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[ind].anim > 0)
	{
		if (sdl->obj[ind].move)
		{
			if (sdl->obj[ind].anim > 58)
				sdl->obj[ind].anim = 1;
			sdl->obj[ind].anim++;
		}
		else if (sdl->obj[ind].atack)
		{
			if (sdl->obj[ind].anim > 58)
				sdl->obj[ind].anim = 1;
			sdl->obj[ind].anim++;
		}
		move_enemy(sdl, ind);
	}
}

void	put_enemy(t_sdl *sdl, int ind, int x, int size)
{
	int	i;
	int	j;
	int	color;
	int	y;

	y = (WIN_H - size) / 2 + (atan((sdl->height - sdl->obj[ind].p.v[2])
		/ sdl->obj[ind].len)) / sdl->ang + sdl->y_ang_i;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if ((i + x) < 0 || (i + x) > sdl->size ||
					(sdl->l[i + x].v[2] < sdl->obj[ind].len))
				break ;
			color = texturebmp(sdl, (float)i / size, (float)j / size /
					sdl->obj[ind].fram + (float)(sdl->obj[ind].anim / 15) /
					sdl->obj[ind].fram, sdl->obj[ind].txtr);
			if ((color & 255) != 255)
				put_pixel(sdl, i + x + sdl->off, j + y, color);
			j++;
		}
		i++;
	}
}

void	draw_enemy(void *s, int ind)
{
	int		l;
	float	size;
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	size = atan(sdl->obj[ind].size / sdl->obj[ind].len) / sdl->ang;
	l = xon_screen(sdl, set_v(sdl->obj[ind].p.v[0],
				sdl->obj[ind].p.v[1], sdl->obj[ind].p.v[2]));
	if (sdl->obj[ind].txtr == 14)
		sdl->obj[ind].fram = 8;
	else
		sdl->obj[ind].fram = 4;
	put_enemy(sdl, ind, l - size / 2, size);
}
