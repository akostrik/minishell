#############################################################################################
#                                                                                           #
#                                           MAKEFILE                                        #
#                                                                                           #
#############################################################################################

NAME	= minishell

LIBFT	= make bonus -C ./libft

SRC_DIR	= srcs/

OBJ_DIR	= objs/

FILES	=	prompt.c \
			parser_expand.c \
			array_utils.c \
			parser_cmd.c \
			parser_cmd_add.c \
			parser_cmd_utils.c \
			lst_utils.c \
			parser_utils.c \
			signal.c \
			executor.c \
			manage_redir.c \
			heredoc.c \
			manage_builtins.c \
			manage_fork.c \
			find_cmd_path.c \
			utils.c \
			ft_echo.c \
			ft_exit.c  \
			ft_env.c \
			ft_export.c \
			ft_unset.c \
			ft_cd.c \
			ft_cd_utils.c \
			ft_pwd.c \
			builtins_utils.c

SRCS	= $(addprefix $(SRC_DIR), $(FILES))

OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

FLAGS	= -Wall -Wextra -Werror -g3

LIB		= -Llibft -lft -lreadline # -L /usr/local/opt/readline/lib

INCL	= -I ./includes/ -I ./libft/ # -I /usr/local/opt/readline/include


objs/%.o : ./srcs/%.c
			mkdir -p $(OBJ_DIR)
			cc $(FLAGS) $(INCL) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(LIBFT)
			cc $(OBJS) -o $(NAME) $(LIB)

clean:
			make -C ./libft clean
			rm -rf ${OBJ_DIR}

fclean: 	clean
			rm -rf $(NAME) ./libft/libft.a

re: 		fclean all

.PHONY : 	all clean fclean re
