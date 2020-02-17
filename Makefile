# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aannara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:24:05 by aannara           #+#    #+#              #
#    Updated: 2020/01/29 15:06:33 by aannara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

all:
	gcc -o $(NAME) main.c draw.c load.c vect.c loop.c raycast.c \
	doorx.c doory.c bmp.c skybox.c object.c actfunc.c \
	animfunc.c text.c enemy.c weapon.c set.c tiles.c tiles2.c \
	load_res.c \
	tiles3.c hp.c -I include -L lib -l SDL2-2.0.0 -lSDL2_mixer  -O3
