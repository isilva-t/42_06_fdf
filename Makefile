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

SRCS = $(GNL) ./src/00_fdf.c \
	./src/11_get_map.c \
	./src/12_get_map_utils.c \
	./src/21_get_map_ready_to_show.c \
	./src/22_set_limits.c \
	./src/31_do_mlx_stuff.c \
	./src/32_set_color_based_on_z.c \
	./src/33_draw_line.c \
	./src/88_utils.c \
	./src/99_free_stuff.c

OBJS = ${SRCS:.c=.o}
MSG0 = @echo "Compiling..."
MSG1 = @echo "_________________________________________________________________ Compiled!"

all: $(NAME)

$(NAME):
	$(MSG0);
	@make -C $(LIBFT_DIR) --silent
	@$(CC) ${CFLAGS} $(SRCS) $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	$(MSG1)
	
c: 
	@make -C $(LIBFT_DIR) --silent
	@$(CC) ${CFLAGS} $(SRCS) -D PRINT_COORDS=1 $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	$(MSG1)

d: 
	@make -C $(LIBFT_DIR) --silent
	@$(CC) ${CFLAGS} $(SRCS) -D PRINT_DIMENSIONS=1 $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)
	$(MSG1)


clean:
	@make clean -C $(LIBFT_DIR) --silent
	@rm -rf ${OBJS}

fclean: clean
	@make fclean -C $(LIBFT_DIR) --silent
	@rm -rf ${NAME}

re: fclean all
ret: fclean t
.PHONY: all clean fclean re
