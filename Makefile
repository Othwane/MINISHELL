# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/11 05:43:13 by aasselma          #+#    #+#              #
#    Updated: 2023/08/23 04:30:22 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c utils_minishell.c signals.c print_errors.c ft_itoa.c ./parsing/errors.c \
		./parsing/get_tokens.c ./parsing/count_token_len.c \
		./parsing/libft_functions.c ./parsing/handel_syntax_error.c \
		./parsing/get_command.c ./parsing/free.c ./parsing/get_variable.c \
		./parsing/utils.c ./parsing/search_and_replace.c ./parsing/search_for_var.c \
		./parsing/remove_qoutes.c ./parsing/env_parser.c ./parsing/remove_dollarsign.c \
		./execution/exec.c ./execution/getpath.c ./execution/exec_utils.c  \
		./execution/exec_redir.c ./execution/herdoc.c  \
		./builtins/echo_b.c ./builtins/pwd_b.c ./builtins/builtins.c ./builtins/cd_b.c ./builtins/exit_b.c \
		./builtins/export_b.c ./builtins/unset_b.c ./builtins/env_b.c ./builtins/builtins_utils.c

OBJ	= $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LDFLAGS = "-L/goinfre/aasselma/homebrew/opt/readline/lib"

CPPFLAGS = "-I/goinfre/aasselma/homebrew/opt/readline/include"

RM = rm -f

cc = cc

all: $(NAME)

$(NAME) : $(OBJ)
	@$(cc) $(CFLAGS)  -lreadline -lcurses $(LDFLAGS) $(CPPFLAGS)  $(OBJ) -o $(NAME)
	@printf "\033[1;32mfiles compiled successfully \033[0m\n"

clean:
	@$(RM) $(OBJ)
	@printf "\033[1;32mobjects files removed successfully\033[0m\n"

fclean: clean
	@$(RM) $(NAME)

re : fclean $(NAME)
