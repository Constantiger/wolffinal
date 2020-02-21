/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:14:16 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:28:28 by aannara          ###   ########.fr       */
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
	printf("door x %i\n", sdl->obj[i].lock);
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
	printf("door y %i\n", sdl->obj[i].lock);
}

void	act_obj(void *s, int i)
{
	t_sdl *sdl;

	i = 0;
	sdl = (t_sdl*)s;
	printf("knight\n");
}

void	act_score(void *s, int i)
{
	t_sdl *sdl;

	sdl = (t_sdl*)s;
	printf("score\n");
	sdl->score++;
	change_score(sdl);
	sdl->obj[i].p.v[0] = 1000.0;
	sdl->obj[i].p.v[1] = 1000.0;
}

void	act_key(void *s, int i)
{
	t_sdl *sdl;

	sdl = (t_sdl*)s;
	printf("key\n");
	sdl->key++;
	sdl->obj[i].p.v[0] = 1000.0;
	sdl->obj[i].p.v[1] = 1000.0;
}
