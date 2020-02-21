/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:24:05 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 16:04:39 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		read_map(t_sdl *sdl, char *s, char *name)
{
	int	fd;
	int	red;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (0);
	red = read(fd, s, 1001);
	next_map(sdl, s, red);
	return (red);
}

void	set_map(t_sdl *s, char *map, int k, int j)
{
	int	i;

	i = 0;
	while (k++ < 1002)
	{
		if (map[k] == '\n')
		{
			if (s->msx > i)
				s->msx = i;
			i = 0;
			j++;
		}
		else if (map[k] == 'E')
		{
			s->msy = j;
			break ;
		}
		else
		{
			s->m[i][j] = map[k];
			i++;
		}
		j += i / 100;
		i = i / ((i / 100) * 99 + 1);
	}
}

int		load_map(t_sdl *s, char *name)
{
	char	map[1001];
	char	err;

	err = 0;
	if (read_map(s, map, name) == 0)
	{
		write(1, "file error\n", 11);
		return (1);
	}
	s->msx = 100;
	s->msy = 100;
	set_map(s, map, -1, 0);
	if ((err = valid_map(s)) != 1)
	{
		err += '0';
		write(1, &err, 1);
		write(1, " map error\n", 11);
		return (0);
	}
	s->bs = 350 / s->msx;
	return (1);
}

void	load_obj_help(t_sdl *sdl, int i, int j)
{
	if (isdoory(sdl, i, j))
		push_doory(sdl, i, j);
	if (isdoorx(sdl, i, j))
		push_doorx(sdl, i, j);
	if (isobj(sdl, i, j))
		push_obj(sdl, i, j);
	if (isscor(sdl, i, j))
		push_score(sdl, i, j);
	if (iskey(sdl, i, j))
		push_key(sdl, i, j);
	if (isenem(sdl, i, j))
		push_enemy(sdl, i, j);
	if (isarrow(sdl, i, j))
		push_arrows(sdl, i, j);
	if (ishp(sdl, i, j))
		push_hp(sdl, i, j);
	if (isend(sdl, i, j))
		push_end(sdl, i, j);
}

char	load_obj(t_sdl *sdl)
{
	int		i;
	int		j;
	char	player;

	player = 0;
	i = 0;
	j = 0;
	while (j < sdl->msy)
	{
		while (i < sdl->msx)
		{
			if (isplayer(sdl, i, j))
			{
				player = 1;
				sdl->r.p = set_v(i + 0.5, j + 0.5, 0.5);
			}
			load_obj_help(sdl, i, j);
			i++;
		}
		j++;
		i = 0;
	}
	if (!player)
		write(1, "no player\n", 10);
	return (player);
}
