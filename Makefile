NAME		=	philo

FILES		=	main.c\
				brain_thread.c\
				free_philo.c\
				init_data.c\
				init_philo.c\
				my_usleep.c\
				parsing.c\
				philosophers.c\
				routine.c\

SRCS		=	$(addprefix srcs/, $(FILES))

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

SANITIZE	=	-fsanitize=thread -g

### RULES ###

$(NAME):		$(OBJS)
				@echo "Compiling..."
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@echo "Done."

.c.o:
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

sanitize:		$(OBJS)
				@echo "Compiling with sanitize..."
				@$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -o $(NAME)
				@echo "Done."

all:			$(NAME)

clean:
				@echo "Cleaning..."
				@rm -f $(OBJS)
				@echo "Cleaned."

fclean:			clean
				@rm -f $(NAME)

re :			fclean $(NAME)

.PHONY: sanitize all clean fclean re
