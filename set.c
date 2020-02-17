/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:13:54 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:11:06 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		init_sdl(t_sdl *s)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		write(1, "Can't init\n", 11);
		return (1);
	}
	s->win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_L, WIN_H,
		SDL_WINDOW_SHOWN);
	if (s->win == NULL)
	{
		write(1, "Can't create window\n", 20);
		return (1);
	}
	s->ren = SDL_CreateRenderer(s->win, -1, 0);
	if (s->ren == NULL)
	{
		write(1, "Can't create renderer\n", 22);
		return (1);
	}
	return (0);
}

int		init(t_sdl *s)
{
	if (init_sdl(s) != 0)
		return (1);
	s->text = SDL_CreateTexture(s->ren, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_L, WIN_H);
	if (s->text == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	s->img = malloc(WIN_L * WIN_H * sizeof(int));
	if (s->img == NULL)
	{
		write(1, "Can't create texture\n", 21);
		return (1);
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		write(1, "Can't create mixer\n", 19);
		return (1);
	}
	return (0);
}

void	set1(t_sdl *s)
{
	s->game_over = 0;
	s->run = 1;
	s->x_ang_i = 0;
	s->x_ang = 0.0;
	s->y_ang = 0.0;
	s->y_ang_i = 0;
	s->off = 400;
	s->pov = PI / 3;
	s->size = WIN_L - s->off;
	s->hsize = s->size / 2;
	s->ang = s->pov / s->size;
	s->height = 0.5;
	s->bord = 0.5;
	s->pls = 0.2;
	s->spd = 0.24;
	s->spdx = 0.0;
	s->spdy = 0.0;
	s->bs = 30;
	s->hbs = (float)s->bs / 2;
	s->msence = 0.01;
	s->doorx_count = 0;
	s->doory_count = 0;
	s->obj_count = 0;
	s->text_count = 0;
	s->sky_i = 5;
}

void	set2(t_sdl *s)
{
	s->tang = NULL;
	s->gmusic = NULL;
	s->gchunk = NULL;
	s->jump = 0;
	s->gforce = 0.005;
	s->spdz = 0.0;
	s->sp = 0;
	s->mleft = 0;
	s->up = 0;
	s->down = 0;
	s->left = 0;
	s->right = 0;
	s->w = 0;
	s->s = 0;
	s->a = 0;
	s->d = 0;
	s->q = 0;
	s->e = 0;
	s->f = 0;
	s->rb = 0;
	s->mk = 0;
	s->mouse_look = 1;
	s->p = s->r.p;
	s->txt_count = 0;
	s->score = 0;
}

void	set(t_sdl *s)
{
	set1(s);
	set2(s);
	s->key = 0;
	s->lock = 0;
	s->unlock = 0;
	s->arrows = 10;
	s->reload = 0;
	s->hp = 100;
	s->weap_fr = 5;
	push_text(s, s->off + 20, 20, "Score:");
	push_text(s, s->off + 120, 20, "0000");
	push_text(s, s->off + 200, HWH, "Door is closed, find key!");
	push_text(s, s->off + 300, HWH, "Door open now!");
	push_text(s, s->off + 20, WIN_H - 52, "HP:");
	push_text(s, s->off + 70, WIN_H - 52, "100");
	push_text(s, s->off + 250, WIN_H - 52, "ARROWS:");
	push_text(s, s->off + 370, WIN_H - 52, "0010");
	push_text(s, s->off + 300, HWH, "GAME OVER!");
}
