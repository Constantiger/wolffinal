/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 10:58:48 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 14:44:42 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	act_arrow(void *s, int i)
{
	t_sdl *sdl;

	sdl = (t_sdl*)s;
	set_arrows(sdl, 5);
	sdl->obj[i].p.v[0] = 1000.0;
}

void	push_proj(t_sdl *sdl)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].pl.v[0] = cos(sdl->x_ang) * 0.1;
		sdl->obj[sdl->obj_count].pl.v[1] = sin(sdl->x_ang) * 0.1;
		sdl->obj[sdl->obj_count].pl.v[2] = sin(sdl->y_ang) * 0.1;
		sdl->obj[sdl->obj_count].p = sdl->r.p;
		move_proj(sdl, sdl->obj_count);
		sdl->obj[sdl->obj_count].size = 0.04;
		sdl->obj[sdl->obj_count].bord = 0.1;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].txtr = 13;
		sdl->obj[sdl->obj_count].iter = 0;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].proj = 1;
		sdl->obj[sdl->obj_count].enem = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_obj;
		sdl->arr_i = sdl->obj + sdl->obj_count;
		sdl->obj_count++;
	}
}

void	reload(t_sdl *sdl)
{
	int	i;

	i = 0;
	if (sdl->reload > 0)
	{
		sdl->weap_fr = sdl->reload / 10;
		if (!sdl->game_over)
			sdl->spd = 0.1;
		sdl->reload++;
		if (sdl->reload > 59)
			sdl->reload = 0;
	}
	else
	{
		if (!sdl->game_over)
			sdl->spd = 0.23;
		sdl->weap_fr = 5;
	}
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].proj == 1)
			move_proj(sdl, i);
		i++;
	}
}

void	shoot(t_sdl *sdl)
{
	if (!sdl->reload && sdl->arrows > 0)
	{
		sdl->reload = 1;
		push_proj(sdl);
		set_arrows(sdl, -1);
		if (Mix_PlayChannel(-1, sdl->gchunk, 0) == -1)
		{
			write(1, "error play chan\n", 16);
			quit(sdl);
		}
	}
}

void	draw_weapon(t_sdl *sdl, int size)
{
	int		i;
	int		j;
	float	tx;
	float	ty;
	int		color;

	i = 0;
	j = 3;
	while (j < size / 32 * 15)
	{
		while (i < size)
		{
			tx = (float)i / size;
			ty = ((float)j / (size / 32 * 15) + sdl->weap_fr) / 6;
			color = texturebmp(sdl, tx, ty, 12);
			if ((color & 255) != 255)
				put_pixel(sdl, i + sdl->off, j + WIN_H - size / 32 * 15, color);
			i++;
		}
		i = 0;
		j++;
	}
}
