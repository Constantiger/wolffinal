/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:52:39 by aannara           #+#    #+#             */
/*   Updated: 2020/01/29 15:01:59 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

char	ishp(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'h' || sdl->m[x][y] == 'H');
}

char	isenem(t_sdl *sdl, int x, int y)
{
	return (sdl->m[x][y] == 'm' || sdl->m[x][y] == 'M');
}
