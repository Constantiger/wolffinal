/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 18:40:51 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:29:00 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	anim_doorx(void *s, int i)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[i].anim == 400)
		sdl->obj[i].anim = 0;
	if (sdl->obj[i].anim > 0 && sdl->obj[i].anim < 100)
		sdl->obj[i].p.v[1] += 0.01;
	if (sdl->obj[i].anim > 300 && sdl->obj[i].anim < 400)
		sdl->obj[i].p.v[1] -= 0.01;
	if (sdl->obj[i].anim > 0)
		sdl->obj[i].anim++;
	sdl->doorx[sdl->obj[i].ind].v[1] = sdl->obj[i].p.v[1];
}

void	anim_doory(void *s, int i)
{
	t_sdl	*sdl;

	sdl = (t_sdl*)s;
	if (sdl->obj[i].anim == 400)
		sdl->obj[i].anim = 0;
	if (sdl->obj[i].anim > 0 && sdl->obj[i].anim < 100)
		sdl->obj[i].p.v[0] += 0.01;
	if (sdl->obj[i].anim > 300 && sdl->obj[i].anim < 400)
		sdl->obj[i].p.v[0] -= 0.01;
	if (sdl->obj[i].anim > 0)
		sdl->obj[i].anim++;
	sdl->doory[sdl->obj[i].ind].v[0] = sdl->obj[i].p.v[0];
}
