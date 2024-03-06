# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 17:25:20 by ecabanas          #+#    #+#              #
#    Updated: 2024/03/06 18:27:31 by erosas-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell
HEADER		=		inc/minishell.h
USERNAME	:=		$(shell whoami)
OS			:=		$(shell uname)

SRC			=		src
OBJ			=		obj
INC_DIR		=		inc
SRCS		=		$(wildcard $(SRC)/*.c)
OBJS		=		$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
DEPS		=		$(addsuffix .d, $(basename $(SRCS)))


LIBFT		=		-L ./lib/libft -lft
#LREADLINE	=		-L /Users/$(USERNAME)/.brew/Cellar/readline/8.2.1/lib
#IREADLINE	=		-I /Users/$(USERNAME)/.brew/Cellar/readline/8.2.1/include
LREADLINE	=		-L /Users/$(USERNAME)/.brew/opt/readline/lib
IREADLINE	=		-I /Users/$(USERNAME)/.brew/opt/readline/include

CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror -MMD

RM			=		rm -rf

######################################################################

SYSTEM_RULE := $(NAME)

all: $(SYSTEM_RULE)

libft:
	make -C lib/libft

$(NAME):  libft $(OBJS)
	$(CC) $(CFLAGS) $(LREADLINE) $(LIBFT) $(IREADLINE) -lreadline $(OBJS) -o $@
# DAVANT -o: -fsanitize='address,undefined'

#linux: libft $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	$(CC) $(CFLAGS) -I $(INC_DIR) $(IREADLINE) -g -c $< -o $@
# DAVANT LA -c: -fsanitize='address,undefined'

$(OBJ):
	mkdir $@

clean:
	make -C lib/libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C lib/libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
