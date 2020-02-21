/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:34:24 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 16:34:28 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	anim(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->obj_count)
	{
		if (sdl->obj[i].anim)
			(*sdl->obj[i].anim_f)((void*)sdl, i);
		i++;
	}
}

void	change_score(t_sdl *sdl)
{
	sdl->txt[1].str[0] = sdl->score / 10 + '0';
	sdl->txt[1].str[1] = sdl->score % 10 + '0';
}

void	logic(t_sdl *sdl)
{
	move(sdl);
	jump_f(sdl);
	obj_len(sdl);
	anim(sdl);
	show_lock(sdl);
	show_unlock(sdl);
	reload(sdl);
	if (-sdl->x_ang > PI)
		sdl->x_ang += PI2;
	if (sdl->x_ang > PI)
		sdl->x_ang -= PI2;
	if (sdl->y_ang < -0.65)
		sdl->y_ang = -0.65;
	if (sdl->y_ang > 0.75)
		sdl->y_ang = 0.75;
	if (sdl->height > 0.95)
		sdl->height = 0.95;
	if (sdl->height < 0.05)
		sdl->height = 0.05;
	sdl->y_ang_i = (int)(sdl->y_ang / sdl->ang);
	sdl->x_ang_i = (int)(sdl->x_ang / sdl->ang + sdl->tngm) % sdl->tngm;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *p;

	p = (unsigned char*)b;
	while (len)
	{
		*(p++) = (unsigned char)c;
		len--;
	}
	return (b);
}

void	loop(t_sdl *sdl)
{
	while (sdl->run)
	{
		while (SDL_PollEvent(&sdl->event) != 0)
		{
			if (sdl->event.type == SDL_QUIT)
				sdl->run = 0;
			if (sdl->event.type == SDL_KEYDOWN)
				keydown(sdl);
			if (sdl->event.type == SDL_KEYUP)
				keyup(sdl);
			if (sdl->event.type == SDL_MOUSEMOTION)
				mousemove(sdl);
			if (sdl->event.type == SDL_MOUSEBUTTONDOWN)
				mousedown(sdl);
		}
		ft_memset(sdl->img, 0, WIN_L * WIN_H * sizeof(int));
		key_logic(sdl);
		logic(sdl);
		draw(sdl);
		SDL_UpdateTexture(sdl->text, NULL, sdl->img, WIN_L * sizeof(int));
		SDL_RenderClear(sdl->ren);
		SDL_RenderCopy(sdl->ren, sdl->text, NULL, NULL);
		SDL_RenderPresent(sdl->ren);
	}
}
