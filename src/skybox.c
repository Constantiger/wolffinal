/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:11:12 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 16:05:00 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		sky_text(t_sdl *sdl, float x, float y, int ind)
{
	int	size;
	int	ox;
	int	oy;

	size = sdl->my[sdl->sky_i] / 3;
	if (ind == 4 || ind == 5)
		x = 1.0 - x;
	if (ind == 0)
	{
		ox = size;
		oy = 0;
	}
	else if (ind == 1)
	{
		ox = size;
		oy = 2 * size;
	}
	else
	{
		ox = (ind - 2) * size;
		oy = size;
	}
	return (*(sdl->bmp[sdl->sky_i] + ((int)(y * size) + oy)
				* sdl->mx[sdl->sky_i] + ((int)(x * size) + ox)));
}

void	draw_top(int x, int y, t_vect p, t_sdl *sdl)
{
	float	tx;
	float	ty;
	float	t;
	float	d;
	int		ya;

	while (y >= 0)
	{
		ya = -sdl->y_ang_i - HWH + y;
		ya = (ya + sdl->tngm) % sdl->tngm;
		t = sdl->tang[ya];
		d = 0.5 / t / p.v[2];
		tx = d * (0.5 - p.v[0]) + 0.5;
		ty = d * (0.5 - p.v[1]) + 0.5;
		tx = tx - (int)tx;
		ty = ty - (int)ty;
		put_pixel(sdl, x + sdl->off, y,
			sky_text(sdl, ty, tx, 0));
		y--;
	}
}

void	draw_bot(int x, int y, t_vect p, t_sdl *sdl)
{
	float	tx;
	float	ty;
	float	t;
	float	d;
	int		ya;

	while (y < WIN_H)
	{
		ya = sdl->y_ang_i + HWH - y;
		ya = (ya + sdl->tngm) % sdl->tngm;
		t = sdl->tang[ya];
		d = 0.5 / t / p.v[2];
		tx = d * (0.5 - p.v[0]) + 0.5;
		tx = tx - (int)tx;
		ty = d * (0.5 - p.v[1]) + 0.5;
		ty = ty - (int)ty;
		put_pixel(sdl, x + sdl->off, y,
			sky_text(sdl, ty, 1.0 - tx, 1));
		y++;
	}
}

void	draw_sky(t_sdl *sdl)
{
	int		i;
	float	j;
	float	k;
	float	h;
	int		color;

	i = 0;
	while (i < sdl->size)
	{
		k = atan(0.5 / sdl->l[i].v[2]) / sdl->ang;
		j = -k + sdl->y_ang_i;
		k = k + sdl->y_ang_i;
		h = k - j;
		draw_top(i, j + HWH, sdl->l[i], sdl);
		while (j < k)
		{
			color = sky_text(sdl, sdl->l[i].v[sdl->l[i].c % 2] -
					(int)(sdl->l[i].v[sdl->l[i].c % 2]),
					(1.0 - (k - j) / h), sdl->l[i].c);
			put_pixel(sdl, i + sdl->off, j + HWH, color);
			j++;
		}
		i++;
	}
}

t_vect	cast_cube(t_sdl *sdl, int a_i)
{
	t_vect	res;
	t_vect	cent;

	cent = set_v(0.5, 0.5, 0.5);
	res.v[0] = 0.5;
	res.v[1] = 0.5;
	if (a_i > sdl->qpi && a_i <= sdl->qpi3)
	{
		set_vc(&res, 0.5 + 1 / sdl->tang[a_i] / 2, 1.0, 4);
	}
	else if (a_i > sdl->qpi3 && a_i <= sdl->qpi5)
	{
		set_vc(&res, 0.0, 0.5 - sdl->tang[a_i] / 2, 5);
	}
	else if (a_i > sdl->qpi5 && a_i <= sdl->qpi7)
	{
		set_vc(&res, 0.5 - 1 / sdl->tang[a_i] / 2, 0.0, 2);
	}
	else if ((a_i > sdl->qpi7 && a_i < sdl->tngm)
		|| (a_i >= 0 && a_i <= sdl->qpi))
	{
		set_vc(&res, 1.0, 0.5 + sdl->tang[a_i] / 2, 3);
	}
	res.v[2] = leng(cent, res);
	return (res);
}
