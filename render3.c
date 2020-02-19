/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:59:17 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 15:04:50 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		texturebmp(t_sdl *sdl, float x, float y, int ind)
{
	int	tx;
	int	ty;

	tx = x * (sdl->mx[ind] - 1);
	ty = y * (sdl->my[ind] - 1);
	return (*(sdl->bmp[ind] + ty * sdl->mx[ind] + tx));
}

void	draw_flor(int x, int y, t_vect p, t_sdl *sdl)
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
		d = sdl->height / t / p.v[2];
		tx = d * (sdl->r.p.v[0] - p.v[0]) + sdl->r.p.v[0];
		tx = tx - (int)tx;
		ty = d * (sdl->r.p.v[1] - p.v[1]) + sdl->r.p.v[1];
		ty = ty - (int)ty;
		put_pixel(sdl, x + sdl->off, y,
		texturebmp(sdl, tx, ty, 1));
		y++;
	}
}

void	draw_ceil(int x, int y, t_vect p, t_sdl *sdl)
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
		d = (1.0 - sdl->height) / t / p.v[2];
		tx = d * (sdl->r.p.v[0] - p.v[0]) + sdl->r.p.v[0];
		ty = d * (sdl->r.p.v[1] - p.v[1]) + sdl->r.p.v[1];
		if (isceil(sdl, (int)tx, (int)ty))
		{
			tx = tx - (int)tx;
			ty = ty - (int)ty;
			put_pixel(sdl, x + sdl->off, y,
			texturebmp(sdl, tx, ty, 4));
		}
		y--;
	}
}

float	leng(t_vect a, t_vect b)
{
	float	dy;
	float	dx;

	dy = a.v[1] - b.v[1];
	dx = a.v[0] - b.v[0];
	return (sqrt(dx * dx + dy * dy));
}

int		xon_screen(t_sdl *sdl, t_vect v)
{
	float	a;
	int		l;
	float	dy;
	float	dx;

	dy = v.v[1] - sdl->r.p.v[1];
	dx = v.v[0] - sdl->r.p.v[0];
	a = atan(dy / dx) - sdl->x_ang;
	if (dx < 0)
		a = a - 3.141592;
	if (a > 3.141592)
		a -= 6.28318;
	if (a < -3.141592)
		a += 6.28318;
	l = a / sdl->ang + sdl->hsize;
	return (l);
}
