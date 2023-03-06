
SRCS	= 	main.c \
			pipex.c \
			redirections.c \
			exe.c \
			exeutils.c \
			utils.c \
			wait_input.c \
			check_str.c \
			error.c \
			split_pipe.c \
			print_matrix.c \
			ft_make_lst.c \
			create_history.c\
			get_next_line.c\
			search_redirection.c\
			clean_quotes.c\
			builtins.c \
			ft_echo.c\
			ft_cd.c \
			get_pwd.c\
			ft_export.c\
			ft_unset.c search_cmds.c\
			ft_endquotes.c\
			search_files.c\
			ft_check_dollar.c\
			ft_strjoin_n.c\
			signals.c\

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC	= gcc

RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address

LIBFT = libft/libft.a

PATHLIB = libft/

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LIBFT} ${OBJS}
				${CC} ${CFLAGS} ${LIBFT} ${OBJS} -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include -o ${NAME}

${LIBFT}:
			@make -C ${PATHLIB}

all:		${NAME}

clean:
				@make clean -C ${PATHLIB}
				${RM} ${OBJS} ${OBJB}

fclean: 	clean
				@make fclean -C ${PATHLIB}
				${RM} ${NAME}

re: 		fclean all

.PHONY:		all clean fclean re
