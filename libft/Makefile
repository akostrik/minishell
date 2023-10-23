NAME	= libft.a

FILES	= ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_isalnum.c \
		  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_striteri.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \

FILES_B	= ${FILES} \
		  ft_lstadd_back_bonus.c \
		  ft_lstadd_front_bonus.c \
		  ft_lstclear_bonus.c \
		  ft_lstdelone_bonus.c \
		  ft_lstiter_bonus.c \
		  ft_lstlast_bonus.c \
		  ft_lstmap_bonus.c \
		  ft_lstnew_bonus.c \
		  ft_lstsize_bonus.c \

SRC_DIR	= srcs/

OBJ_DIR	= objs/

SRCS	= ${addprefix ${SRC_DIR}, ${FILES}}

SRCS_B	= ${addprefix ${SRC_DIR}, ${FILES_B}}

OBJS	= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

OBJS_B	= ${SRCS_B:${SRC_DIR}%.c=${OBJ_DIR}%.o}

RM	= rm -rf

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

INCL	= -I ./

objs/%.o : ./srcs/%.c
			@mkdir -p ${OBJ_DIR}
			cc ${FLAGS} ${INCL} -c $< -o $@

all:		${NAME}

bonus:		${OBJS_B}
		ar -crs ${NAME} ${OBJS_B}

${NAME}:	${OBJS}
		ar -crs ${NAME} ${OBJS}

clean:
		${RM} ${OBJ_DIR}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all bonus clean fclean re
