SRC_DIR					= ./

SRC = ${SRC_DIR}philo.c ${SRC_DIR}parse.c ${SRC_DIR}error.c ${SRC_DIR}utils.c ${SRC_DIR}philo_utils.c ${SRC_DIR}philosopher.c  ${SRC_DIR}philo_manager.c ${SRC_DIR}ft_putnbr.c ${SRC_DIR}philosopher_utils.c

OBJS = ${SRC:.c=.o}

NAME 		= philo
CC 			= gcc

CFLAGS 		=  -Wall -Wextra -Werror 

.c.o:		
			${CC} ${CFLAGS} -c -I${SRC_DIR} $< -o ${<:.c=.o} -lpthread

all: 		${NAME}

${NAME}: 	${OBJS}
		 	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

clean:
	   		rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re