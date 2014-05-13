#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/25 12:34:27 by cwagner           #+#    #+#              #
#    Updated: 2014/03/27 20:37:24 by cwagner          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_S = 		serveur
NAME_C =		client

DEBUG =		yes

ifeq ($(DEBUG), yes)
	CC = clang
	CFLAGS=-Wall -Wextra -Werror -pedantic -g3
else
	CC = gcc
	CFLAGS=-Wall -Wextra -Werror
endif

INCLUDES = 	-I includes/

SRCS =		srcs/
LIB = 		libft/


SDIR = 		$(SRCS)serveur/
SFILES =	main.c\
			create.c\
			interpret.c\
			func1.c

SERVER =	$(addprefix $(SDIR), $(SFILES))


CDIR =		$(SRCS)client/
CFILES =	main.c\
			create.c


CLIENT =	$(addprefix $(CDIR), $(CFILES))

OBJ_S = 	$(SERVER:.c=.o)
OBJ_C = 	$(CLIENT:.c=.o)

all: libft $(NAME_S) $(NAME_C)

ifeq ($(DEBUG), yes)
	@echo
	@echo "\033[33m[Generation]\033[0m mode debug"
	@echo
else
	@echo
	@echo "\033[33m[Generation]\033[0m Mode: \033[32m[Release]\033[0m"
	@echo
endif

libft:
	@echo "\033[31m[Libft] \033[0m" | tr -d '\n'
	make -C $(LIB)

$(NAME_S): $(OBJ_S)
	@echo "\033[32m[Building Server] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ_S) -L $(LIB) -lft

$(NAME_C): $(OBJ_C)
	@echo "\033[32m[Building Client] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ_C) -L $(LIB) -lft

remake:
	@echo "\033[31m[Re-Libft] \033[0m" | tr -d '\n'
	make re -C $(LIB)

%.o: %.c
	@echo "\033[33m[Doing object] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@echo "\033[34m[Cleaning] \033[0m" | tr -d '\n'
	rm -f $(OBJ_S) $(OBJ_C)

fclean: clean
	@echo "\033[34m[Filecleaning] \033[0m" | tr -d '\n'
	rm -f $(NAME_S) $(NAME_C)

ffclean: fclean
	make fclean -C $(LIB)

re: fclean all

rre: remake re

run: all
	@echo "\033[32m[Running Binary]\033[0m" | tr -d '\n'
	@echo ""
	@./$(NAME_S) 4242
	@./$(NAME_C) 127.0.0.1 4242
	@make clean

debug: re
	gdb ./$(NAME_C)

.PHONY: clean fclean re
