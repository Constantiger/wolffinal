/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:24:10 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 15:25:29 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	move_enemy_helper(t_sdl *sdl, int ind)
{
	if (sdl->obj[ind].len < 1.1)
	{
		if (sdl->obj[ind].move)
		{
			sdl->obj[ind].move = 0;
			sdl->obj[ind].atack = 1;
			sdl->obj[sdl->obj_count].anim = 1;
			sdl->obj[ind].txtr = 11;
		}
	}
	else if (!sdl->obj[ind].atack)
	{
		sdl->obj[ind].move = 1;
		sdl->obj[ind].txtr = 10;
	}
	if (sdl->obj[ind].atack && sdl->obj[ind].anim == 57)
	{
		if (sdl->obj[ind].len < 1.5)
			set_hp(sdl, -10);
		sdl->obj[ind].move = sdl->obj[ind].see;
		sdl->obj[ind].atack = 0;
		sdl->obj[sdl->obj_count].anim = 10;
		sdl->obj[ind].txtr = 10;
	}
}

void	move_enemy(t_sdl *sdl, int ind)
{
	see_enemy(sdl, ind);
	if (!sdl->obj[ind].atack && sdl->obj[ind].see &&
			sdl->obj[ind].len < 8.0)
	{
		sdl->obj[ind].move = 1;
		sdl->obj[ind].txtr = 10;
	}
	if (sdl->obj[ind].p.v[0] - sdl->obj[ind].pl.v[0] < 0.1 &&
			sdl->obj[ind].p.v[0] - sdl->obj[ind].pl.v[0] > -0.1 &&
			sdl->obj[ind].p.v[1] - sdl->obj[ind].pl.v[1] < 0.1 &&
			sdl->obj[ind].p.v[1] - sdl->obj[ind].pl.v[1] > -0.1)
	{
		sdl->obj[ind].move = 0;
		sdl->obj[sdl->obj_count].anim = 10;
		sdl->obj[ind].txtr = 10;
	}
	else
		move_enemy_helper(sdl, ind);
	if (sdl->obj[ind].move)
		coll_enemy(sdl, ind);
}
