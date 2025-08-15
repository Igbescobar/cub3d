# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igngonza <igngonza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 12:53:54 by igngonza          #+#    #+#              #
#    Updated: 2025/08/15 13:32:45 by igngonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := cub3d

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
IFLAGS      := -Iinclude -Ilibft -Imlx
MLX_FLAGS := -Lmlx -lmlx -lXext -lX11 -lm -lz

SRC_DIR     := src
OBJ_DIR     := obj
LIBFT_DIR   := libft
MLX_DIR     := mlx


SRC_FILES   := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)

OBJ_FILES   := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))


LIBFT       := $(LIBFT_DIR)/libft.a
MLX         := $(MLX_DIR)/libmlx.a

# === Frameworks (for macOS only, comment out if not needed) ===
# MLX_FLAGS   := -Lmlx -lmlx -framework OpenGL -framework AppKit

LD_FLAGS    := $(MLX_FLAGS) -L$(LIBFT_DIR) -lft


all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ_FILES) $(LD_FLAGS) -o $(NAME)
	@echo "✅ Compiled $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Cleaned object files"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "🧼 Full clean done"

re: fclean all

.PHONY: all clean fclean re