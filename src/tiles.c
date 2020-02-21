/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:43:19 by aannara           #+#    #+#             */
/*   Updated: 2020/02/21 15:33:57 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	iswall(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] != '1');
}

char	isplayer(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'p' || sdl->m[x][y] == 'P');
}

char	isdoory(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'y' || sdl->m[x][y] == 'Y' ||
		sdl->m[x][y] == 't' || sdl->m[x][y] == 'T');
}

char	isdoorx(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'x' || sdl->m[x][y] == 'X' ||
		sdl->m[x][y] == 'z' || sdl->m[x][y] == 'Z');
}

char	isceil(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'c' || sdl->m[x][y] == 'C' ||
		sdl->m[x][y] == 'y' || sdl->m[x][y] == 'x' ||
		sdl->m[x][y] == 'p' || sdl->m[x][y] == 'o' ||
		sdl->m[x][y] == 'g' || sdl->m[x][y] == 'k' ||
		sdl->m[x][y] == 't' || sdl->m[x][y] == 'z' ||
		sdl->m[x][y] == 'm' || sdl->m[x][y] == 'a' ||
		sdl->m[x][y] == 'h' || sdl->m[x][y] == 'n');
}
