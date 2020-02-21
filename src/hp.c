/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 13:39:18 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 16:21:17 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	push_hp(t_sdl *sdl, int x, int y)
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
		sdl->obj[sdl->obj_count].txtr = 15;
		sdl->obj[sdl->obj_count].iter = 0;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].proj = 0;
		sdl->obj[sdl->obj_count].enem = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_hp;
		sdl->obj_count++;
	}
}

void	act_hp(void *s, int i)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	sdl->score++;
	set_hp(sdl, 15);
	sdl->obj[i].p.v[0] = 1000.0;
	sdl->obj[i].p.v[1] = 1000.0;
}
