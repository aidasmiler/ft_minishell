# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/07 14:50:36 by airodrig          #+#    #+#              #
#    Updated: 2022/05/16 18:02:12 by airodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=		minishell

S		=		src/

U		=		utils/

P		=		parser/

B		=		builtins/

E		=		executor/

O		=		obj/

H		=		 -I inc/ -I lib/libft/inc -I /Users/$(USER)/.brew/opt/readline/include

LIBS	=		-lreadline -L /Users/$(USER)/.brew/opt/readline/lib  -L lib/libft -lft

UTILS_FILES	=	free_utils.c \
				print_utils.c \
				other_utils.c \
				print_error.c \
				signals_utils.c \
				prompt.c \
				banner.c

PARS_FILES	=	tokenizer.c \
				lexer_parser_utils.c \
				heredoc_utils.c \
				lst_utils.c \
				parser.c

BUILT_FILES	=	echo_pwd_exit_env.c \
				export.c \
				cd_env_unset.c \
				main_builtins.c

EXEC_FILES	=	executor.c \
				executor_utils.c

UTILS	=	$(addprefix $U, $(UTILS_FILES))

PARSER	=	$(addprefix $P, $(PARS_FILES))

BUILTINS	=	$(addprefix $B, $(BUILT_FILES))

EXECUTOR	=	$(addprefix $E, $(EXEC_FILES))

FILES	=	env_to_lst.c \
			$(UTILS) \
			$(PARSER) \
			$(BUILTINS) \
			$(EXECUTOR) \
			main.c

SRCS	=	$(addprefix $S, $(FILES))

OBJS	=		$(SRCS:$S%.c=$O%.o)

CC		=		gcc

RM		=		rm -rf

CFLAGS	=		-Wall -Werror -Wextra -g3 #-fsanitize=address

NOCOL		=	\033[0m
RED			=	\033[1;31m
ORG			=	\033[0;33m
YEL			=	\033[1;33m
GRN			=	\033[1;32m
BLU			=	\033[0;34m
CYN			=	\033[0;36m
PUR			=	\033[0;35m

#Black        0;30     Dark Gray     1;30
#Red          0;31     Light Red     1;31
#Green        0;32     Light Green   1;32
#Brown/Orange 0;33     Yellow        1;33
#Blue         0;34     Light Blue    1;34
#Purple       0;35     Light Purple  1;35
#Cyan         0;36     Light Cyan    1;36
#Light Gray   0;37     White         1;37

all: $(NAME)
	@printf "\r$(GRN) Minishell compiled                                                \
	                                                            $(NOCOL)\n"
	@printf "\t$(PUR)- All libft objs done$(NOCOL)\n"
	@printf "\t$(BLU)- All minishell objs done$(NOCOL)\n"
	@printf "\t\t$(YEL)- Minishell up todate and ready to run$(NOCOL)\n"

$O%.o: $S%.c
	@[ -d $O ] || mkdir $O
	@[ -d $O$U ] || mkdir $O$U
	@[ -d $O$P ] || mkdir $O$P
	@[ -d $O$E ] || mkdir $O$E
	@[ -d $O$B ] || mkdir $O$B
	@printf "$(BLU)#$(NOCOL)"
	@$(CC) $(CFLAGS) $H -c $< -o $@

$(NAME): $(OBJS)
	@make -s -C lib/libft
	@$(CC) $(CFLAGS) $H $(SRCS) $(LIBS) -o $(NAME)
	@[ -e $(NAME) ]

bonus: all

clean:
	@make clean -s -C lib/libft
	@${RM} $O

fclean: clean
	@rm -f lib/libft/libft.a > /dev/null
	@${RM} ${NAME}
	@echo "$(CYN) 🧼🧼🧼 All clean! 🧼🧼🧼 $(NOCOL)"

re: fclean all

normi:
	@echo "$(PUR) 🔍🔍 Checking Norminette 🔎🔎$(NOCOL)"
	@norminette $S

.PHONY: all clean fclean re normi bonus
