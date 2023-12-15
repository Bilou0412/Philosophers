NAME		=	philo

HEADER		=	inc/

CC			=	cc

CFLAGS		=	 -Werror -Wall -Wextra -g -I $(HEADER)  -fsanitize=thread 

SRCS		=	srcs/main.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME) 

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm $(NAME)

re			:	fclean all
