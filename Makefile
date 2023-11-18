# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 16:43:24 by aurban            #+#    #+#              #
#    Updated: 2023/11/18 19:52:01 by aurban           ###   ########.fr        #
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
	init_param.c \
	captain_hook.c \
	ft_image_update_colors.c

SRC_FILES:= $(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC_FILES))

all: fractol

$(LIBMLX):
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/$@ ./
	
$(LIBFT):
	@make -C $(LIBFT_PATH)/ all
	@make -C $(LIBFT_PATH)/ clean
	@mv $(LIBFT_PATH)/$@ ./

DO_LIBS: $(LIBFT) $(LIBMLX)

$(NAME): $(SRC_OBJECTS) | DO_LIBS
	@$(CC) $^ $(LIBS) $(CFLAGS) -o $@
	
clean: 
	@$(RM) $(SRC_OBJECTS)

fclean: clean
	@$(RM) $(NAME) $(LIBS)

re: fclean all

.PHONY: all clean fclean re libft libmlx