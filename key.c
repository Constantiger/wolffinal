/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:17:00 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 15:52:31 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	key_logic3(t_sdl *sdl)
{
	if (sdl->d)
	{
		sdl->spdx += cos(sdl->x_ang + HPI) * sdl->spd;
		sdl->spdy += sin(sdl->x_ang + HPI) * sdl->spd;
	}
	if (sdl->rb)
	{
		if (sdl->sky_i == 5)
			sdl->sky_i = 6;
		else
			sdl->sky_i = 5;
		sdl->rb = 0;
	}
	if (sdl->f)
	{
		click(sdl);
		sdl->f = 0;
	}
	if (sdl->mleft)
	{
		shoot(sdl);
		sdl->mleft = 0;
	}
}

void	key_logic2(t_sdl *sdl)
{
	if (sdl->sp && sdl->jump == 0)
	{
		sdl->sp = 0;
		sdl->height = 0.5;
		sdl->jump = 1;
		sdl->spdz = 0.08;
	}
	if (sdl->w)
	{
		sdl->spdx += cos(sdl->x_ang) * sdl->spd;
		sdl->spdy += sin(sdl->x_ang) * sdl->spd;
	}
	if (sdl->s)
	{
		sdl->spdx += -cos(sdl->x_ang) * sdl->spd;
		sdl->spdy += -sin(sdl->x_ang) * sdl->spd;
	}
	if (sdl->a)
	{
		sdl->spdx += cos(sdl->x_ang - HPI) * sdl->spd;
		sdl->spdy += sin(sdl->x_ang - HPI) * sdl->spd;
	}
}

void	key_logic(t_sdl *sdl)
{
	if (sdl->up)
		sdl->height += 0.05;
	if (sdl->down)
		sdl->height -= 0.05;
	if (sdl->right)
		sdl->spdx = sdl->spd;
	if (sdl->left)
		sdl->spdx = -sdl->spd;
	if (sdl->q)
		sdl->x_ang -= 0.02;
	if (sdl->e)
		sdl->x_ang += 0.02;
	key_logic2(sdl);
	key_logic3(sdl);
}

void	keydown(t_sdl *sdl)
{
	sdl->up = (sdl->event.key.keysym.sym == SDLK_UP) ? 1 : sdl->up;
	sdl->down = (sdl->event.key.keysym.sym == SDLK_DOWN) ? 1 : sdl->down;
	sdl->right = (sdl->event.key.keysym.sym == SDLK_RIGHT) ? 1 : sdl->right;
	sdl->left = (sdl->event.key.keysym.sym == SDLK_LEFT) ? 1 : sdl->left;
	sdl->q = (sdl->event.key.keysym.sym == SDLK_q) ? 1 : sdl->q;
	sdl->w = (sdl->event.key.keysym.sym == SDLK_w) ? 1 : sdl->w;
	sdl->e = (sdl->event.key.keysym.sym == SDLK_e) ? 1 : sdl->e;
	sdl->a = (sdl->event.key.keysym.sym == SDLK_a) ? 1 : sdl->a;
	sdl->s = (sdl->event.key.keysym.sym == SDLK_s) ? 1 : sdl->s;
	sdl->d = (sdl->event.key.keysym.sym == SDLK_d) ? 1 : sdl->d;
	sdl->rb = (sdl->event.key.keysym.sym == SDLK_r) ? 1 : sdl->rb;
	sdl->f = (sdl->event.key.keysym.sym == SDLK_f) ? 1 : sdl->f;
	if (sdl->event.key.keysym.sym == SDLK_ESCAPE)
		sdl->run = 0;
	sdl->sp = (sdl->event.key.keysym.sym == SDLK_SPACE) ? 1 : sdl->sp;
	sdl->mk = (sdl->event.key.keysym.sym == SDLK_m) ? 1 : sdl->mk;
}

void	keyup(t_sdl *sdl)
{
	sdl->up = (sdl->event.key.keysym.sym == SDLK_UP) ? 0 : sdl->up;
	sdl->down = (sdl->event.key.keysym.sym == SDLK_DOWN) ? 0 : sdl->down;
	sdl->right = (sdl->event.key.keysym.sym == SDLK_RIGHT) ? 0 : sdl->right;
	sdl->left = (sdl->event.key.keysym.sym == SDLK_LEFT) ? 0 : sdl->left;
	sdl->q = (sdl->event.key.keysym.sym == SDLK_q) ? 0 : sdl->q;
	sdl->w = (sdl->event.key.keysym.sym == SDLK_w) ? 0 : sdl->w;
	sdl->e = (sdl->event.key.keysym.sym == SDLK_e) ? 0 : sdl->e;
	sdl->a = (sdl->event.key.keysym.sym == SDLK_a) ? 0 : sdl->a;
	sdl->s = (sdl->event.key.keysym.sym == SDLK_s) ? 0 : sdl->s;
	sdl->d = (sdl->event.key.keysym.sym == SDLK_d) ? 0 : sdl->d;
	sdl->sp = (sdl->event.key.keysym.sym == SDLK_SPACE) ? 0 : sdl->sp;
	sdl->rb = (sdl->event.key.keysym.sym == SDLK_r) ? 0 : sdl->rb;
	sdl->f = (sdl->event.key.keysym.sym == SDLK_f) ? 0 : sdl->f;
	if (sdl->event.key.keysym.sym == SDLK_m)
	{
		sdl->mk = 0;
		if (!sdl->mouse_look)
			SDL_ShowCursor(SDL_DISABLE);
		else
			SDL_ShowCursor(SDL_ENABLE);
		sdl->mouse_look = !sdl->mouse_look;
	}
}
