/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:21:55 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 16:21:02 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	isend(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'n' || sdl->m[x][y] == 'N');
}

void	push_end_help(t_sdl *sdl, int x, int y)
{
	if (sdl->doorx_count < 100)
	{
		sdl->doorx[sdl->doorx_count].v[0] = x + 0.5;
		sdl->doorx[sdl->doorx_count].v[1] = y + 0.5;
		sdl->doorx_count++;
	}
}

void	act_end(void *s, int i)
{
	t_sdl	*sdl;

	i = 0;
	sdl = (t_sdl*)s;
	if (!sdl->has_next)
		return ;
	if (!load_map(sdl, sdl->next_level))
		quit(sdl);
	sdl->obj_count = 0;
	sdl->doorx_count = 0;
	sdl->doory_count = 0;
	if (!load_obj(sdl))
		quit(sdl);
}

void	push_end(t_sdl *sdl, int x, int y)
{
	push_end_help(sdl, x, y);
	if (sdl->obj_count < 200)
	{
		sdl->obj[sdl->obj_count].p.v[0] = x + 0.5;
		sdl->obj[sdl->obj_count].p.v[1] = y + 0.5;
		sdl->obj[sdl->obj_count].p.v[2] = 0.45;
		sdl->obj[sdl->obj_count].size = 0.9;
		sdl->obj[sdl->obj_count].bord = 0.5;
		sdl->obj[sdl->obj_count].dr = 0;
		sdl->obj[sdl->obj_count].anim = 0;
		sdl->obj[sdl->obj_count].iter = 1;
		if (islock(sdl, x, y))
			sdl->obj[sdl->obj_count].lock = 1;
		else
			sdl->obj[sdl->obj_count].lock = 0;
		sdl->obj[sdl->obj_count].ind = sdl->doorx_count - 1;
		sdl->obj[sdl->obj_count].draw_f = &draw_obj;
		sdl->obj[sdl->obj_count].act_f = &act_end;
		sdl->obj_count++;
	}
}
