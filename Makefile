# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/05/03 13:58:48 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BUILD = build

CC = cc

SRC = $(wildcard pipe/*.c)

SRCB = $(wildcard pipe_bonus/*.c)

LIBFT = libft

OBJ = $(patsubst %.c, %.o, $(SRC))

OBJB = $(patsubst %.c, %.o, $(SRCB))

PIPE = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

PIPE_BONUS = $(patsubst %.o, $(BUILD)/%.o, $(OBJB))

CFLAGS = -g -Wall -Wextra -Werror

$(BUILD)/%.o: %.c Makefile
	@mkdir -p $(BUILD)/pipe
	@mkdir -p $(BUILD)/pipe_bonus
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME) : $(PIPE)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(PIPE) -o $(NAME) -L./libft -lft

bonus: $(PIPE_BONUS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(PIPE_BONUS) -o $(NAME) -L./libft -lft

fclean: clean
	rm -rf $(NAME) $(BUILD)
	
clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJ) $(OBJB)

re: fclean all

.PHONY: all clean fclean bonus re