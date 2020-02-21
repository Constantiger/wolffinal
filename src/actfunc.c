/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:14:16 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 16:20:42 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	act_doorx(void *s, int i)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[i].lock && sdl->key)
	{
		sdl->unlock = 1;
		sdl->key--;
		sdl->obj[i].lock = 0;
	}
	if (sdl->obj[i].lock && sdl->lock == 0)
	{
		sdl->lock = 1;
	}
	else if (!sdl->obj[i].anim && !sdl->obj[i].lock)
		sdl->obj[i].anim = 1;
}

void	act_doory(void *s, int i)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[i].lock && sdl->key)
	{
		sdl->unlock = 1;
		sdl->key--;
		sdl->obj[i].lock = 0;
	}
	if (sdl->obj[i].lock && sdl->lock == 0)
	{
		sdl->lock = 1;
	}
	else if (!sdl->obj[i].anim && !sdl->obj[i].lock)
		sdl->obj[i].anim = 1;
}

void	act_obj(void *s, int i)
{
	t_sdl *sdl;

	i = 0;
	sdl = (t_sdl*)s;
}

void	act_score(void *s, int i)
{
	t_sdl *sdl;

	sdl = (t_sdl*)s;
	sdl->score++;
	change_score(sdl);
	sdl->obj[i].p.v[0] = 1000.0;
	sdl->obj[i].p.v[1] = 1000.0;
}

void	act_key(void *s, int i)
{
	t_sdl *sdl;

	sdl = (t_sdl*)s;
	sdl->key++;
	sdl->obj[i].p.v[0] = 1000.0;
	sdl->obj[i].p.v[1] = 1000.0;
}
