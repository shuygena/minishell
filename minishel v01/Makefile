NAME =			minishell

CC =			gcc

FLAGS =			-Werror -Wextra -Wall -g

RM =			rm -rf

DIR_HEADERS =	./

HEADER = minishell.h

LIBFT =			libft/libft.a

RL = 			-L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include -lreadline

SRC =			main.c parser.c parser2.c preparser.c \
				parser1.c commands.c pipes1.c redirects.c \
				ft_error.c get_next_line.c get_next_line_utils.c \
				ft_exit.c ft_pwd.c ft_echo.c ft_cd.c cd_utlis.c ft_env.c \
				ft_unset.c ft_export2.c ft_export1.c ft_export3.c parser3.c \
				parser4.c parser5.c parser_dol.c signal.c

#COLORS
OFF_COLOR		=	\033[0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
L_BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
L_BLUE			=	\033[0;36m

.PHONY:			all, clean, fclean, re

all:			$(NAME)

$(NAME) :		$(SRC) $(HEADER)
				@make -C ./libft
				@$(CC) $(FLAGS) $(SRC) $(LIBFT) $(RL) -o $(NAME)
				@echo "$(GREEN)Minishell is complited!$(OFF_COLOR)"

clean:
				@$(RM) libft/*.o
				@echo "${RED}Object files deleted!${OFF_COLOR}"

fclean:			clean
				@$(RM) libft.a $(NAME)
				@echo "${RED}Program deleted!${OFF_COLOR}"


re:				fclean all