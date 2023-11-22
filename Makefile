# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 16:43:24 by aurban            #+#    #+#              #
#    Updated: 2023/11/22 00:57:51 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC:=gcc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Werror -Wextra -I$(INCLUDE_PATH) -ldl -lglfw -pthread -lm# -g3 -fsanitize=address
RM:=rm -rf

NAME:=fractol
LIBFT=libft.a
LIBMLX = libmlx42.a
LIBS:=$(LIBFT) $(LIBMLX)

SRC_PATH:=src
LIBFT_PATH:=./libft
LIBMLX_PATH	:= ./MLX42

RENDING_PATH=Rendering
COMPUTING_PATH=Computing
UTILS_PATH=Utils
HOOKS_PATH=Hooks

SRC_FILES:= main.c \
	$(RENDING_PATH)/renderer.c \
	$(RENDING_PATH)/generator.c \
	$(RENDING_PATH)/colors.c \
	$(RENDING_PATH)/camera.c \
	$(COMPUTING_PATH)/sets_formulas.c \
	$(COMPUTING_PATH)/ft_atoz.c \
	$(COMPUTING_PATH)/iter_count.c \
	$(COMPUTING_PATH)/ft_abs.c \
	$(UTILS_PATH)/error_handles.c \
	$(UTILS_PATH)/init_param.c \
	$(HOOKS_PATH)/captain_hook.c

SRC_FILES:= $(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJECTS:= $(patsubst %.c,%.o,$(SRC_FILES))

all: fractol

$(LIBMLX):
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/$@ ./
	$(RM) $(LIBMLX_PATH)/build
	$(RM) $(LIBMLX_PATH)/CmakeFiles
	
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