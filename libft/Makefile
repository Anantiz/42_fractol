# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 06:06:39 by aurban            #+#    #+#              #
#    Updated: 2023/11/19 12:57:24 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_NAME:=libft.a
LIB_FT_PATH:=.

CC:=gcc
INCLUDE_PATH= ../includes
CFLAGS:=-Wall -Werror -Wextra -I$(INCLUDE_PATH) -g3# -fsanitize=address

LIB_FT_FILES:=ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_isascii.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \
	ft_uitoa.c \
	ft_printf.c \
	ft_uitohex.c \
	ft_ltohex.c \
	ft_ultohex.c \
	ft_send_to_buffer.c \
	ft_arg_to_buffer.c \
	ft_lltoa.c \
	ft_atoldb.c \
	ft_atoll.c

LIB_FT_FILES:= $(addprefix $(LIB_FT_PATH)/,$(LIB_FT_FILES))
LIB_FT_OBJECTS:= $(patsubst %.c,%.o,$(LIB_FT_FILES))

all:$(LIBFT_NAME)
	@echo libft all

$(LIBFT_NAME): $(LIB_FT_OBJECTS)
	@echo compiling libft
	@$(AR) rcs $@ $^

clean: 
	@$(RM) $(LIB_FT_OBJECTS)

fclean: clean
	@$(RM) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re