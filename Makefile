CC := cc
# CFLAGS := -Wall -Wextra -Werror

INCLUDE_DIR := include
SRC_DIRS := src
# BUILD_DIR := build
# BONUS_DIRS := 
LIBFTDIR := libft

LIBFT := $(LIBFTDIR)/libft.a
INCLUDE := $(INCLUDE_DIR)/fdf.h
# INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INCLUDE))
# INCLUDE_BONUS := $(INCLUDE_DIR)/minitalk_bonus.h

SRC := fdf.c gnl.c gen_map.c gen_map_utils_1.c gen_map_utils_2.c draw_line.c draw_map.c \
		state_changing_0.c state_changing_1.c projection.c utils_1.c utils_2.c gradient.c
SRC := $(addprefix $(SRC_DIRS)/,$(SRC))
OBJ := $(SRC:.c=.o)

NAME := fdf

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME)
	@echo "\033[1;32m$(NAME) \033[0;32mhas been compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re lib