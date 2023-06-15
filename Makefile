# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 05:43:13 by aasselma          #+#    #+#              #
#    Updated: 2023/06/15 15:53:58 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =  errors.c minishell.c minishell_utils.c count_token_len.c libft_functions.c

OBJ	= $(SRC:%.c=%.o)

FLAGS = -Wall -Wextra -Werror

RM = rm -f

cc = cc

#  -fsanitize=address

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


