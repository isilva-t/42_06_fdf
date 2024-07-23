# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 16:42:03 by isilva-t          #+#    #+#              #
#    Updated: 2024/07/11 11:23:19 by isilva-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libs/libft/
LIBFT = ./libs/libft/libft.a

GNL = ./libs/gnl/get_next_line.c \
	./libs/gnl/get_next_line_utils.c
FT_PRINTF = ./libs/ft_printf/ft_printf.c \
	./libs/ft_printf/pf_print_ptr.c \
	./libs/ft_printf/pf_put_nbr_base.c 

MLX = -Lminilibx-linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -O3
NAME = fdf

SRCS = $(GNL) fdf.c \
	./src/00_read_and_handle.c \
	./src/01_get_map.c \
	./src/99_free_stuff.c

OBJS = ${SRCS:.c=.o}
MSG1 = @echo "_________________________________________________________________ Compiled!"

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_DIR)
	@$(CC) ${CFLAGS} $(SRCS) $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	$(MSG1)
	
t: 
	@make -C $(LIBFT_DIR)
	@$(CC) ${CFLAGS} $(SRCS) -D PRINT=1 $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	$(MSG1)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf ${OBJS}

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf ${NAME}

re: fclean all
ret: fclean t
.PHONY: all clean fclean re
