# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 13:21:11 by tacarlen          #+#    #+#              #
#    Updated: 2021/10/24 20:24:08 by tacarlen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strmapi.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstiter.c ft_lstclear.c ft_lstmap.c

OBJS	= ${SRCS:.c=.o}

BONOBJ	= ${BONUS:.c=.o}

HEADER	= libft.h

RM		= rm -f

GCC		= gcc

FLAGS	= -Wall -Wextra -Werror

.c.o:	${HEADER}
		@${GCC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			@ar rc ${NAME} ${OBJS}
			@ranlib ${NAME}

all: 	${NAME}

bonus: 		all ${BONOBJ} ${OBJS}
			ar rc ${NAME} ${BONOBJ}
			ranlib ${NAME}

clean:
		@${RM} ${OBJS} ${BONOBJ}

fclean:	clean
		@${RM} ${NAME}

re:		fclean clean all

.PHONY : all clean fclean re bonus
