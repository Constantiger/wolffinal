/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:07:03 by aannara           #+#    #+#             */
/*   Updated: 2020/02/19 12:34:00 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	set_tang(t_sdl *s)
{
	int	i;

	i = 0;
	s->tngm = PI2 / s->ang;
	s->pi = s->tngm / 2;
	s->hpi = s->pi / 2;
	s->pihpi = s->tngm * 3 / 4;
	s->qpi = s->tngm / 8;
	s->qpi3 = s->qpi * 3;
	s->qpi5 = s->qpi * 5;
	s->qpi7 = s->qpi * 7;
	s->tang = (float*)malloc((s->tngm) * sizeof(float));
	if (s->tang == NULL)
	{
		write(1, "tang array error.\n", 18);
		quit(s);
		exit(1);
	}
	while (i < s->tngm)
	{
		s->tang[i] = tan(i * s->ang);
		i++;
	}
}

void	print_map(t_sdl *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < s->msy)
	{
		while (i < s->msx)
		{
			write(1, &s->m[i][j], 1);
			i++;
		}
		write(1, "\n", 1);
		j++;
		i = 0;
	}
}

char	check(t_vect *r)
{
	char	flag;

	flag = 0;
	if (r->v[0] > 100)
	{
		flag = 1;
		r->v[0] = 100;
	}
	if (r->v[0] < 0)
	{
		flag = 1;
		r->v[0] = 0;
	}
	if (r->v[1] > 100)
	{
		flag = 1;
		r->v[1] = 100;
	}
	if (r->v[1] < 0)
	{
		flag = 1;
		r->v[1] = 0;
	}
	return (flag);
}

void	swapi(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

int		main(int argc, char **argv)
{
	t_sdl	sdl;

	if (init(&sdl))
	{
		write(1, "init error\n", 11);
		quit(&sdl);
	}
	set(&sdl);
	if (!load_map(&sdl, argv[1]))
		quit(&sdl);
	if (!load_obj(&sdl))
		quit(&sdl);
	set_tang(&sdl);
	load_audio(&sdl);
	load_textures(&sdl);
	print_map(&sdl);
	SDL_ShowCursor(SDL_DISABLE);
	music(&sdl);
	loop(&sdl);
	return (0);
}
