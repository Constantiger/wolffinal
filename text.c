/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 12:59:49 by aannara           #+#    #+#             */
/*   Updated: 2019/12/25 14:25:56 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	cpy_str(t_sdl *sdl, int ind, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < 100)
	{
		sdl->txt[ind].str[i] = str[i];
		i++;
	}
	sdl->txt[ind].str[i] = '\0';
}

void	push_text(t_sdl *sdl, int x, int y, const char *str)
{
	if (sdl->txt_count < 100)
	{
		cpy_str(sdl, sdl->txt_count, str);
		sdl->txt[sdl->txt_count].x = x;
		sdl->txt[sdl->txt_count].y = y;
		sdl->txt_count++;
	}
}

void	put_char(t_sdl *s, unsigned char c, int ind, int n)
{
	int	i;
	int	j;
	int	color;
	int	tx;
	int	ty;

	i = 0;
	j = 0;
	while (j < s->my[7] / 16)
	{
		while (i < s->mx[7] / 16)
		{
			tx = (float)(c % 16) / 16 * s->mx[7] + i;
			ty = (float)(c / 16) / 16 * s->my[7] + j;
			color = *(s->bmp[7] + ty * s->mx[7] + tx);
			if (color != 255)
				put_pixel(s, i + s->txt[ind].x + n * s->mx[7] / 32,
						j + s->txt[ind].y, color);
			i++;
		}
		j++;
		i = 0;
	}
}

void	put_text(t_sdl *sdl, int ind)
{
	int	i;

	i = 0;
	while (sdl->txt[ind].str[i] != '\0')
	{
		put_char(sdl, sdl->txt[ind].str[i], ind, i);
		i++;
	}
}
