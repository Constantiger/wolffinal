/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:02:19 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 19:19:03 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	load_texture(t_sdl *sdl, const char *fname)
{
	if (sdl->text_count < 32)
	{
		sdl->bmp[sdl->text_count] = loadbmp(fname,
		&sdl->mx[sdl->text_count],
		&sdl->my[sdl->text_count]);
	}
	sdl->text_count++;
}

void	load_textures(t_sdl *sdl)
{
	load_texture(sdl, "textures/obj.bmp");
	load_texture(sdl, "textures/floor.bmp");
	load_texture(sdl, "textures/wall.bmp");
	load_texture(sdl, "textures/door.bmp");
	load_texture(sdl, "textures/ceil.bmp");
	load_texture(sdl, "textures/cub2.bmp");
	load_texture(sdl, "textures/sky.bmp");
	load_texture(sdl, "textures/berlin.bmp");
	load_texture(sdl, "textures/scor1.bmp");
	load_texture(sdl, "textures/key.bmp");
	load_texture(sdl, "textures/enmove.bmp");
	load_texture(sdl, "textures/enatack.bmp");
	load_texture(sdl, "textures/weapon.bmp");
	load_texture(sdl, "textures/arrow.bmp");
	load_texture(sdl, "textures/endeath.bmp");
	load_texture(sdl, "textures/hp.bmp");
	load_texture(sdl, "textures/wall2.bmp");
	load_texture(sdl, "textures/wall3.bmp");
	load_texture(sdl, "textures/wall4.bmp");
}

void	load_audio(t_sdl *sdl)
{
	sdl->gmusic = Mix_LoadMUS("audio/music.wav");
	if (sdl->gmusic == NULL)
	{
		write(1, "error load music\n", 17);
		quit(sdl);
	}
	sdl->gchunk = Mix_LoadWAV("audio/shoot.wav");
	if (sdl->gchunk == NULL)
	{
		write(1, "error load sound\n", 17);
		quit(sdl);
	}
}

void	free_textures(t_sdl *s)
{
	int	i;

	i = 0;
	while (i < s->text_count)
	{
		free(s->bmp[i]);
		i++;
	}
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
	Mix_Quit();
	SDL_Quit();
	exit(1);
}
