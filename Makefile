NAME		=	philo

HEADER		=	inc/

CC			=	cc

CFLAGS		=	 -Werror -Wall -Wextra -g -I $(HEADER)  -fsanitize=thread  

SRCS		=	srcs/main.c \
				srcs/init_data.c \
				srcs/invalid_arg.c \
				srcs/action.c \
				srcs/utils/ft_atoi.c \
				srcs/utils/ft_isdigit.c \
				srcs/utils/time.c \
				

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME) 

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm $(NAME)

re			:	fclean all
