# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igbescobar <igbescobar@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 12:53:54 by igngonza          #+#    #+#              #
#    Updated: 2025/10/06 14:17:17 by igbescobar       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := cub3d

CC          := cc 
CFLAGS      := -Wall -Wextra -Werror



# === Operating System Detection ===
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	DISTRO := $(shell . /etc/os-release && echo $$ID)
	
	ifeq ($(DISTRO), arch)
		IFLAGS    := -Iinclude -Ilibft -Imlx
		MLX_FLAGS := -Lmlx -lmlx -lXext -lX11 -lm -lz
		MLX_CC    := clang
		CFLAGS    := -Wall -Wextra -Wno-incompatible-pointer-types
	else
		IFLAGS    := -Iinclude -Ilibft -Imlx
		MLX_FLAGS := -Lmlx -lmlx -lXext -lX11 -lm -lz
		MLX_CC    := $(CC)
	endif
else ifeq ($(UNAME_S), Darwin)
	IFLAGS    := -Iinclude -Ilibft -Imlx -I/opt/X11/include
	MLX_FLAGS := -Lmlx -lmlx -L/opt/X11/lib -lXext -lX11 -lm -lz
	MLX_CC    := $(CC)
endif

SRC_DIR     := src
OBJ_DIR     := obj
LIBFT_DIR   := libft
MLX_DIR     := mlx


SRC_FILES   := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)

OBJ_FILES   := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))


LIBFT       := $(LIBFT_DIR)/libft.a
MLX         := $(MLX_DIR)/libmlx.a

LD_FLAGS    := $(MLX_FLAGS) -L$(LIBFT_DIR) -lft

all: os_info $(NAME)

os_info:
ifeq ($(UNAME_S), Linux)
	@echo "🐧 Detected Linux - Using X11 libraries"
else ifeq ($(UNAME_S), Darwin)
	@echo "🍎 Detected macOS - Using frameworks"
endif

$(NAME): $(LIBFT) $(MLX) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ_FILES) $(LD_FLAGS) -o $(NAME)
	@echo "✅ Compiled $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR) CC="$(MLX_CC)"

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

.PHONY: all clean fclean re os_info