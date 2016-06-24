# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcowle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/17 09:29:33 by kcowle            #+#    #+#              #
#    Updated: 2016/06/24 08:37:03 by kcowle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLIB=libft/libft.a

CC=clang

NAME= Wolf3D
SRC = draw_to_image.c get_map.c extras.c main1.c raycastalgo.c
OBJ = $(SRC:.c=.o)

all	:$(NAME)

$(NAME)	:$(OBJ)
	make re -C libft/
	$(CC) -o $(NAME) $(OBJ) $(INCLIB) -lmlx -framework OpenGL -framework AppKit

clean	:
	rm -f $(OBJ)

fclean	:clean
	rm -f $(NAME)

re	: fclean clean all
