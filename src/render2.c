/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:42:00 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 14:50:38 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	draw_map(t_sdl *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < s->msy)
	{
		while (i < s->msx)
		{
			if (s->m[i][j] == '1')
				put_box(s, set_b(i * s->bs + 25, j * s->bs + 25, s->bs), 255);
			i++;
		}
		j++;
		i = 0;
	}
	i = 0;
	while (i < s->obj_count)
	{
		j = s->bs * s->obj[i].bord;
		put_box(s, set_b(s->obj[i].p.v[0] * s->bs + 25 - j / 2,
			s->obj[i].p.v[1] * s->bs + 25 - j / 2, j), c(255, 0, 255));
		i++;
	}
}

void	draw_ray(t_sdl *s, t_ray r)
{
	float	x;
	float	y;
	float	sz;
	int		color;

	color = c(0, 255, 0);
	sz = s->bs * s->bord;
	x = r.p.v[0] * s->bs;
	y = r.p.v[1] * s->bs;
	put_box(s, set_b(x + 25 - sz / 2, y + 25 - sz / 2, sz), color);
	put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang) * 200 + 25,
		y + sin(s->x_ang) * 200 + 25, 0.0), color);
	put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang - s->hsize * s->ang) * 200 + 25,
		y + sin(s->x_ang - s->hsize * s->ang) * 200 + 25, 0.0), color);
	put_line(s, set_v(x + 25, y + 25, 0.0),
		set_v(x + cos(s->x_ang + s->hsize * s->ang) * 200 + 25,
		y + sin(s->x_ang + s->hsize * s->ang) * 200 + 25, 0.0), color);
}

void	draw_skybox(t_sdl *sdl)
{
	int		i;
	t_vect	p;

	p = set_v(0.5, 0.5, 0.5);
	i = 0;
	while (i < sdl->size)
	{
		sdl->ar[i].p = p;
		sdl->ar[i].a_i = (sdl->x_ang_i - sdl->hsize
				+ i + sdl->tngm) % sdl->tngm;
		sdl->l[i] = cast_cube(sdl, sdl->ar[i].a_i);
		i++;
	}
	draw_sky(sdl);
}

void	draw_gui(t_sdl *sdl)
{
	int	i;

	i = 0;
	if (!sdl->game_over)
	{
		while (i < sdl->txt_count - 1)
		{
			if ((i != 2 || (i == 2 && sdl->lock > 0)) &&
					(i != 3 || (i == 3 && sdl->unlock > 0)))
				put_text(sdl, i);
			i++;
		}
	}
	else
	{
		put_text(sdl, sdl->txt_count - 1);
	}
}

int		texture_ind(t_sdl *sdl, int i)
{
	int	tx;

	tx = 2;
	if (sdl->l[i].c == 0)
	{
		if (sdl->r.p.v[1] > sdl->l[i].v[1])
			tx = 2;
		else
			tx = 16;
	}
	else
	{
		if (sdl->r.p.v[0] > sdl->l[i].v[0])
			tx = 17;
		else
			tx = 18;
	}
	return (tx);
}
