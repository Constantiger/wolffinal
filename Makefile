# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aannara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:24:05 by aannara           #+#    #+#              #
#    Updated: 2020/02/17 17:21:33 by aannara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c draw.c load.c vect.c loop.c raycast.c \
	doorx.c doory.c bmp.c skybox.c object.c actfunc.c \
	animfunc.c text.c enemy.c weapon.c weapon2.c set.c tiles.c tiles2.c \
	load_res.c tiles3.c hp.c

OBJ = $(SRC:.c=.o)

FLAGS = -O3

SDL_FLAGS = -I include -I SDL_lib/SDL2.framework/Headers -I SDL_lib/SDL2_mixer.framework/Headers

SDL2 = -framework SDL2 -framework SDL2_mixer -F ./SDL_lib/

SDL2_LOAD = -rpath @loader_path/SDL_lib/

INC = ./inc

NAME = wolf3d

HEADERS = ./inc/head.h ./inc/bmp.h

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(HEADERS)
	gcc -o $(NAME) $(OBJ) $(FLAGS) $(SDL2_LOAD) $(SDL2)

.c.o: $(HEADERS)
	gcc -I$(INC) $(FLAGS) $(SDL_FLAGS) -c $< -o $@

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

