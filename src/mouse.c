/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannara <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:14:39 by aannara           #+#    #+#             */
/*   Updated: 2020/02/18 16:21:33 by aannara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	mousedown(t_sdl *sdl)
{
	if (sdl->mouse_look)
	{
		if (sdl->event.button.button == SDL_BUTTON_LEFT)
			sdl->mleft = 1;
	}
}

void	mousemove(t_sdl *sdl)
{
	if (sdl->mouse_look)
	{
		sdl->x_ang += (sdl->event.motion.x - HWL) * sdl->msence;
		sdl->y_ang -= (sdl->event.motion.y - HWH) * sdl->msence;
		SDL_WarpMouseInWindow(NULL, HWL, HWH);
	}
}
