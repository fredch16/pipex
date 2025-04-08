# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 12:58:21 by fredchar          #+#    #+#              #
#    Updated: 2025/04/08 10:08:39 by fredchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror
INCD := include
SRCD := src
OBJD := obj
LIBFT_DIR := $(INCD)/libft
LIBFT := $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR := $(LIBFT_DIR)/ft_printf
FT_PRINTF := $(FT_PRINTF_DIR)/libftprintf.a

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

# Spinner animation
SPINNER := / - \\ \|

SRCS :=			$(SRCD)/main.c \
				$(SRCD)/parsing.c \
				$(SRCD)/execute.c \


OBJS := $(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

all: $(NAME)

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	@printf "$(YELLOW)Building ft_printf library...$(NC)\n"
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(OBJD)/%.o: $(SRCD)/%.c | $(OBJD)
	@i=0; \
	while [ $$i -lt 4 ]; do \
		printf "\r$(YELLOW)Compiling $<... $${SPINNER:$$i:1}$(NC)"; \
		sleep 0.001; \
		i=$$((i+1)); \
	done
	@$(CC) $(CFLAGS) -I $(INCD) -I $(LIBFT_DIR) -I $(FT_PRINTF_DIR)/include -c $< -o $@
	@printf "\r$(GREEN)Compiled $< successfully!$(NC)\n"

$(OBJD):
	mkdir -p $(OBJD)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf -o $(NAME)
	@printf "$(GREEN)Executable $(NAME) built successfully!$(NC)\n"

clean:
	@printf "$(RED)Cleaning object files...$(NC)\n"
	rm -rf $(OBJD)
	@printf "$(GREEN)Object files cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	@printf "$(RED)Cleaning library and executable...$(NC)\n"
	rm -f $(NAME)
	@printf "$(GREEN)Executable cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re