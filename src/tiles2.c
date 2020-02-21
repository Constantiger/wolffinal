/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:50:38 by aannara           #+#    #+#             */
/*   Updated: 2020/01/29 14:52:31 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	isarrow(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'a' || sdl->m[x][y] == 'A');
}

char	islock(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 't' || sdl->m[x][y] == 'T' ||
			sdl->m[x][y] == 'Z' || sdl->m[x][y] == 'Z');
}

char	isobj(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'o' || sdl->m[x][y] == 'O');
}

char	isscor(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'g' || sdl->m[x][y] == 'G');
}

char	iskey(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'k' || sdl->m[x][y] == 'K');
}
