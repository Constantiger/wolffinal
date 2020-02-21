/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:19:24 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 14:53:38 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	proj_hit(t_sdl *sdl, int ind)
{
	int	i;

	i = 0;
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].iter)
		{
			if (detect(sdl->obj[ind].p, sdl->obj[ind].bord,
						sdl->obj[i].p, sdl->obj[i].bord) &&
					sdl->obj[ind].p.v[2] > (sdl->obj[i].p.v[2]
						- sdl->obj[i].size / 2) &&
					sdl->obj[ind].p.v[2] < (sdl->obj[i].p.v[2]
						+ sdl->obj[i].size / 2))
			{
				sdl->obj[ind].proj = 0;
				sdl->obj[ind].p.v[0] = 1000.0;
				if (sdl->obj[i].enem)
					damage_enemy(sdl, i);
			}
		}
		i++;
	}
}

void	move_proj(t_sdl *sdl, int ind)
{
	sdl->obj[ind].p.v[0] += sdl->obj[ind].pl.v[0];
	sdl->obj[ind].p.v[1] += sdl->obj[ind].pl.v[1];
	sdl->obj[ind].p.v[2] += sdl->obj[ind].pl.v[2];
	if (wallat(sdl, sdl->obj[ind].p.v[0], sdl->obj[ind].p.v[1]))
	{
		sdl->obj[ind].proj = 0;
		sdl->obj[ind].p.v[0] = 1000.0;
	}
	proj_hit(sdl, ind);
	if (sdl->obj[ind].p.v[0] > 100.0 || sdl->obj[ind].p.v[0] < 0.0 ||
			sdl->obj[ind].p.v[1] > 100.0 || sdl->obj[ind].p.v[1] < 0.0)
	{
		sdl->obj[ind].proj = 0;
		sdl->obj[ind].p.v[0] = 1000.0;
	}
}

void	push_arrows(t_sdl *sdl, int x, int y)
{
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.25;
		sdl->obj[sdl->obj_count].size = 0.1;
		sdl->obj[sdl->obj_count].bord = 0.2;
		sdl->obj[sdl->obj_count].dr = 1;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].txtr = 13;
		sdl->obj[sdl->obj_count].iter = 0;
		sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].proj = 0;
		sdl->obj[sdl->obj_count].enem = 0;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_arrow;
		sdl->obj_count++;
	}
}
