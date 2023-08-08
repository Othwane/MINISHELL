# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 05:43:13 by aasselma          #+#    #+#              #
#    Updated: 2023/08/08 01:23:41 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c ./parsing/errors.c ./parsing/get_tokens.c ./parsing/count_token_len.c \
		./parsing/libft_functions.c ./parsing/handel_syntax_error.c ./parsing/get_command.c \
		./parsing/free.c ./parsing/get_variable.c ./parsing/utils.c ./parsing/search_and_replace.c \
		./parsing/reomve_qoutes.c \
		./execution/exec.c ./execution/getpath.c ./execution/exec_utils.c


OBJ	= $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

RM = rm -f

cc = cc

all: $(NAME)

$(NAME) : $(OBJ)
	@$(cc) $(FLAGS) -lreadline $(OBJ) -o $(NAME)
	@printf "\033[1;32mfiles compiled successfully \033[0m\n"

clean:
	@$(RM) $(OBJ)
	@printf "\033[1;32mobjects files removed successfully\033[0m\n"

fclean: clean
	@$(RM) $(NAME)

re : fclean $(NAME)


