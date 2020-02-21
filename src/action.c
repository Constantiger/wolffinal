/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:25:20 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 16:28:53 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	set_hp(t_sdl *sdl, int h)
{
	sdl->hp += h;
	if (sdl->hp > 200)
		sdl->hp = 200;
	if (sdl->hp < 0)
	{
		sdl->game_over = 1;
		sdl->height = 0.05;
		sdl->spd = 0.0;
	}
	sdl->txt[5].str[0] = sdl->hp / 100 + '0';
	sdl->txt[5].str[1] = sdl->hp / 10 - sdl->hp / 100 * 10 + '0';
	sdl->txt[5].str[2] = sdl->hp % 10 + '0';
}

void	set_arrows(t_sdl *sdl, int a)
{
	sdl->arrows += a;
	sdl->txt[7].str[0] = sdl->arrows / 1000 + '0';
	sdl->txt[7].str[1] = sdl->arrows / 100 + '0';
	sdl->txt[7].str[2] = sdl->arrows / 10 + '0';
	sdl->txt[7].str[3] = sdl->arrows % 10 + '0';
}

void	click(t_sdl *sdl)
{
	int		i;
	t_vect	cl;

	i = sdl->obj_count - 1;
	cl.v[0] = sdl->r.p.v[0] + cos(sdl->x_ang) * 0.3;
	cl.v[1] = sdl->r.p.v[1] + sin(sdl->x_ang) * 0.3;
	while (i >= 0)
	{
		if (detect(cl, 0.5, sdl->obj[i].p, sdl->obj[i].bord))
		{
			(*sdl->obj[i].act_f)((void*)sdl, i);
			break ;
		}
		i--;
	}
}

void	show_lock(t_sdl *sdl)
{
	if (sdl->lock > 0)
	{
		sdl->lock++;
		if (sdl->lock > 150)
			sdl->lock = 0;
	}
}

void	show_unlock(t_sdl *sdl)
{
	if (sdl->unlock > 0)
	{
		sdl->unlock++;
		if (sdl->unlock > 150)
			sdl->unlock = 0;
	}
}
