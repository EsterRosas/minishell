# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 16:55:19 by ecabanas          #+#    #+#              #
#    Updated: 2022/03/01 19:55:45 by ecabanas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_bzero.c \
	ft_abs.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_atoi.c	\
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \

SRCBONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c
	
OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f


all: $(NAME)

$(NAME): ${OBJ}
		 ar rcs ${NAME} ${OBJ}
		 ranlib ${NAME}
	
bonus:  ${OBJ} ${OBJBONUS}
		${RM} ${NAME}
		ar rcs ${NAME} ${OBJ} ${OBJBONUS}
		ranlib ${NAME}

clean:	
	${RM} ${OBJ} ${OBJBONUS}

fclean: clean
		${RM} ${NAME} 

re: fclean all


.PHONY: clean fclean re all re bonus
