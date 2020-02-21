# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aannara <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/17 13:24:05 by aannara           #+#    #+#              #
#    Updated: 2020/02/21 15:22:30 by aannara          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./src/main.c ./src/draw.c ./src/load.c ./src/load2.c ./src/vect.c ./src/loop.c ./src/raycast.c \
	./src/doorx.c ./src/doory.c ./src/bmp.c ./src/skybox.c ./src/object.c ./src/actfunc.c ./src/quit.c \
	./src/animfunc.c ./src/text.c ./src/weapon.c ./src/weapon2.c ./src/set.c ./src/tiles.c ./src/tiles2.c \
	./src/load_res.c ./src/tiles3.c ./src/hp.c ./src/move.c ./src/move2.c ./src/key.c ./src/envi.c ./src/mouse.c \
	./src/action.c ./src/end.c ./src/render.c ./src/render2.c ./src/render3.c ./src/enemy.c ./src/enemy2.c ./src/enemy3.c

OBJ = $(SRC:.c=.o)

FLAGS = -O3 -Wall -Wextra -Werror

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

