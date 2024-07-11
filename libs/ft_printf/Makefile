# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 09:55:09 by isilva-t          #+#    #+#              #
#    Updated: 2024/05/08 09:56:21 by isilva-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SOURCES = ft_printf.c \
		  pf_put_nbr_base.c \
		  pf_print_ptr.c

OBJECTS = ${SOURCES:.c=.o}

NAME = libftprintf.a
ARCHIVE = ar -rcs

MSG1 = @echo "________ Compiled Mandatory files!"
MSG2 = @echo "________ Compiled Bonus files!"
MSG3 = @echo "___________ Cleared!"
MSG4 = @echo "_______________ Full Cleared!"

$(NAME):
	@${CC} -c ${CFLAGS} $(SOURCES) 
	@${ARCHIVE} $(NAME) ${OBJECTS}

	
#ma: 
#	cc $(SOURCES) main.c
#	@echo "\n______Test_Compiled_!\n"

#bonus: $(NAME)
#	${CC} -c ${CFLAGS} $(BONUS) 
#	${ARCHIVE} $(NAME) ${BONUS_OBJECTS}
#	${MSG2}
#bo:
#	cc $(BONUS) $(SOURCES)
#	@echo "\n______Bonus_Test_Compiled_!\n"
	
all: ${NAME}

clean:
	@rm -rf ${OBJECTS}


fclean: clean
	@rm -rf ${NAME}


re: fclean all

.PHONY: all bonus clean fclean re ma bo
