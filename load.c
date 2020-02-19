/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:24:05 by aannara           #+#    #+#             */
/*   Updated: 2020/01/31 18:40:09 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		valid_map(t_sdl *s)
{
	int	i;
	int	j;

	if (s->msx < 3 || s->msy < 3)
		return (4);
	i = 0;
	j = 0;
	while (j < s->msy)
	{
		while (i < s->msx)
		{
			if ((i == 0 || i == (s->msx - 1)) && s->m[i][j] != '1')
				return (2);
			if ((j == 0 || j == (s->msy - 1)) && s->m[i][j] != '1')
				return (3);
			i++;
		}
		j++;
		i = 0;
	}
	return (1);
}

int		read_map(char *s)
{
	int	fd;
	int	red;

	fd = open("map.txt", O_RDONLY);
	if (fd < 0)
		return (0);
	red = read(fd, s, 1001);
	return (red);
}

int		load_map(t_sdl *s)
{
	char	map[1001];
	int		i;
	int		j;
	int		k;
	char	err;

	i = 0;
	j = 0;
	k = 0;
	err = 0;
	if (read_map(map) == 0)
	{
		write(1, "file error\n", 11);
		return (1);
	}
	s->msx = 100;
	s->msy = 100;
	while (k < 1002)
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
		if (i == 100)
		{
			i = 0;
			j++;
		}
		k++;
	}
	if ((err = valid_map(s)) != 1)
	{
		err += '0';
		write(1, &err, 1);
		write(1, " map error\n", 11);
		return (0);
	}
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
