# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 05:43:13 by aasselma          #+#    #+#              #
#    Updated: 2023/07/17 22:21:35 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	errors.c minishell.c get_tokens.c count_token_len.c libft_functions.c \
		handel_syntax_error.c get_command.c free.c get_variable.c

OBJ	= $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=address

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


