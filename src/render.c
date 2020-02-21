/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:24:56 by aannara           #+#    #+#             */
/*   Updated: 2020/02/20 16:26:49 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	draw_bmp(t_sdl *sdl, int sx, int sy, int ind)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	while (j < sdl->my[ind])
	{
		while (i < sdl->mx[ind])
		{
			color = *(sdl->bmp[ind] + j * sdl->mx[ind] + i);
			if ((color & 255) != 255)
				put_pixel(sdl, sx + i, sy + j, color);
			i++;
		}
		j++;
		i = 0;
	}
}

void	draw_wall(t_sdl *sdl)
{
	int		i;
	float	j;
	float	k;
	float	h;

	i = 0;
	j = 0;
	while (i < sdl->size)
	{
		k = atan(sdl->height / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
		j = -atan((1.0 - sdl->height) / sdl->l[i].v[2]) /
			sdl->ang + sdl->y_ang_i;
		h = k - j;
		draw_ceil(i, j + HWH, sdl->l[i], sdl);
		while (j < k)
		{
			put_pixel(sdl, i + sdl->off, j + HWH,
				texturebmp(sdl, sdl->l[i].v[sdl->l[i].c]
					- (int)(sdl->l[i].v[sdl->l[i].c]),
				((k - j) / h), texture_ind(sdl, i)));
			j++;
		}
		draw_flor(i, j + HWH, sdl->l[i], sdl);
		i++;
	}
}

void	draw_fow(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->size)
	{
		sdl->ar[i].p = sdl->r.p;
		sdl->ar[i].a_i = (sdl->x_ang_i - sdl->hsize + i + sdl->tngm)
			% sdl->tngm;
		sdl->l[i] = cast_ray(sdl, sdl->ar[i]);
		i++;
	}
	draw_wall(sdl);
}

void	draw_doors(t_sdl *sdl, int f, int l, int i)
{
	float	j;
	float	k;
	float	h;
	int		color;

	j = 0;
	k = atan(sdl->height / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
	j = -atan((1.0 - sdl->height) / sdl->l[i].v[2]) / sdl->ang + sdl->y_ang_i;
	h = k - j;
	while (j < k)
	{
		color = texturebmp(sdl, 1.0 - (float)(i - l) / (f - l),
			(1.0 - (k - j) / h), 3);
		put_pixel(sdl, i + sdl->off, j + HWH, color);
		j++;
	}
}

void	draw(t_sdl *sdl)
{
	int	i;

	draw_ray(sdl, sdl->r);
	draw_skybox(sdl);
	draw_fow(sdl);
	i = 0;
	while (i < sdl->doory_count)
		draw_doory(sdl, i++);
	i = 0;
	while (i < sdl->doorx_count)
		draw_doorx(sdl, i++);
	i = sdl->obj_count - 1;
	while (i >= 0)
	{
		if (sdl->obj[i].dr)
			(*sdl->obj[i].draw_f)(sdl, i);
		i--;
	}
	if (!sdl->game_over)
		draw_weapon(sdl, sdl->size);
	draw_gui(sdl);
	if (sdl->key)
		draw_bmp(sdl, WIN_L - 10 - sdl->mx[9], -70, 9);
	draw_map(sdl);
	put_box(sdl, set_b(sdl->off + sdl->hsize - 3, HWH - 3, 6), 0);
}
