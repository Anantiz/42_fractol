# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 16:43:24 by aurban            #+#    #+#              #
#    Updated: 2023/11/18 11:28:49 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Werror -Wextra -I$(INCLUDE_PATH) -ldl -lglfw -pthread -lm -DEBUG
RM:=rm -rf

NAME:=fractol
LIBFT= libft.a
LIBMLX = libmlx42.a
LIBS:=$(LIBFT) $(LIBMLX)

SRC_PATH:=src
LIBFT_PATH:=./libft
LIBMLX_PATH	:= ./MLX42

SRC_FILES:= main.c \
	renderer.c \
	generator.c \
	sets_formulas.c \
	error_handles.c \
	ft_atoz.c \
	init_param.c

SRC_FILES:= $(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC_FILES))

all: $(NAME)

libmlx: $(LIBMLX)

$(LIBMLX):
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/$@ ./
	
libft: $(LIBFT)

$(LIBFT):
	@make -C $(LIBFT_PATH)/ all
	@make -C $(LIBFT_PATH)/ clean
	@mv $(LIBFT_PATH)/$@ ./

DO_LIBS: libft libmlx

$(NAME): $(SRC_OBJECTS) | DO_LIBS
	@$(CC) $^ $(LIBS) $(CFLAGS) -o $@
	
clean: 
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@$(RM) $(NAME) $(LIBS)

re: fclean all

.PHONY: all clean fclean re libft libmlx
