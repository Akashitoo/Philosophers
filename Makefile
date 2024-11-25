NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -pthread

CFLAGS += -fsanitize=thread 

SRC =	philo.c \
		god.c \
		utils.c \
		routine.c \
		init.c \
		eating.c \
		exit.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	TSAN_OPTIONS=second_deadlock_stack=1 $(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo  "\033[0;32m ✢ 𝙋𝙃𝙄𝙇𝙊 𝙄𝙎 𝙍𝙀𝘼𝘿𝙔 !"
clean:
	rm -rf $(OBJS)
	echo "\033[0;31m ✢ 𝘼𝙇𝙇 𝙊𝘽𝙅𝙀𝘾𝙏𝙎 𝙃𝘼𝙑𝙀 𝘽𝙀𝙀𝙉 𝘿𝙀𝙇𝙀𝙏𝙀𝘿🚮"

fclean: clean
	rm -rf $(NAME)
	echo " ✢ 𝙋𝙃𝙄𝙇𝙊 𝙒𝘼𝙎 𝘿𝙀𝙇𝙀𝙏𝙀𝘿🚮"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
