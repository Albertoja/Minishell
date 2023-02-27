
SRCS	= 	builtins.c \
			check_str.c \
			clean_quotes.c\
			create_history.c\
			error.c \
			exe.c \
			exeutils.c \
			ft_cd.c \
			ft_check_dollar.c\
			ft_echo.c\
			ft_endpipe.c\
			ft_endquotes.c\
			ft_export.c\
			ft_make_lst.c \
			ft_strjoin_n.c\
			ft_unset.c\
			get_next_line.c\
			get_next_line_aux.c\
			get_pwd.c\
			heredoc.c\
			main.c \
			pipex.c \
			print_matrix.c \
			redirections.c \
			search_cmds.c\
			search_files.c\
			search_redirection.c\
			signals.c\
			split_pipe.c \
			utils.c \
			wait_input.c \
			ft_export2.c \

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
