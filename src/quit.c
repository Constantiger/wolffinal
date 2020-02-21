/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:59:51 by sdiego            #+#    #+#             */
/*   Updated: 2020/02/19 17:01:28 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	quit_help(void)
{
	Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	exit(1);
}

void	quit(t_sdl *s)
{
	if (s->win != NULL)
		SDL_DestroyWindow(s->win);
	s->win = NULL;
	if (s->ren != NULL)
		SDL_DestroyRenderer(s->ren);
	s->ren = NULL;
	if (s->text != NULL)
		SDL_DestroyTexture(s->text);
	s->text = NULL;
	if (s->img != NULL)
		free(s->img);
	s->img = NULL;
	if (s->tang != NULL)
		free(s->tang);
	s->tang = NULL;
	free_textures(s);
	if (s->gmusic != NULL)
		Mix_FreeMusic(s->gmusic);
	s->gmusic = NULL;
	if (s->gchunk != NULL)
		Mix_FreeChunk(s->gchunk);
	s->gchunk = NULL;
	quit_help();
}
