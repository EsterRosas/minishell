# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 17:25:20 by erosas-c          #+#    #+#              #
#    Updated: 2024/03/21 18:54:06 by erosas-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		minishell
HEADER		=		inc/minishell.h
USERNAME	:=		$(shell whoami)

SRC_DIR		=		src/

INC_DIR		=		inc
SRC_FILES	=		builtins.c		    ft_export.c			parser2.c			syntax.c		\
					builtins_utils.c	ft_export_edit.c	parser_rmquotes.c	trim.c			\
					ctrl_chars.c		ft_export_utils.c	parser_utils.c		utils.c			\
					error.c			    ft_unset.c			parser_utils2.c		var_utils.c		\
					exec.c			    heredoc.c	 		parser_utils3.c		var_utils2.c 	\
					exec_utils.c		lexer_delquotes.c	pipe_utils.c		variables.c		\
					exec_utils2.c		lexer_utils.c		prompt.c			variables2.c	\
					ft_cd.c			    list2array.c		signal.c			parser_utils4.c	\
					ft_echo.c		    main.c				subsplit.c			var_utils3.c	\
					ft_exit.c		    parser.c			subsplit_utils.c	var_utils4.c
					
OBJ_DIR		=		obj/
OBJ_FILES	=		$(SRC_FILES:.c=.o)
OBJS		=		$(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES	=		$(SRC_FILES:.c=.d)
DEPS		=		$(addprefix $(OBJ_DIR), $(DEP_FILES))

LIBFT		=		lib/libft/libft.a
LREADLINE	=		-L /Users/$(USERNAME)/.brew/opt/readline/lib
IREADLINE	=		-I /Users/$(USERNAME)/.brew/opt/readline/include

INCLUDE		=		-I inc/ -I lib/libft/ $(IREADLINE)

CC			=		gcc
CFLAGS		=		-Wall -Wextra -Werror -MMD #-fsanitize='address'

RM			=		rm -rf

######################################################################

all: libft $(NAME)

libft:
	make -C lib/libft/

$(NAME):	$(OBJ_DIR) $(OBJS)
		$(CC) $(CFLAGS) $(LREADLINE) -lreadline -L lib/libft/ -lft $(OBJS) -o $@

$(OBJ_DIR):
		mkdir $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(LIBFT) Makefile
		$(CC) $(CFLAGS) $(INCLUDE) -g -c $< -o $@

clean:
		@make -C lib/libft/ clean
		$(RM) $(OBJS) $(DEPS)
	
fclean: clean
		@make -C lib/libft/ fclean
		$(RM) $(NAME)
		$(RM) $(OBJ_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all libft clean fclean re
