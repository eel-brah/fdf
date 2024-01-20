CC := cc
# CFLAGS := -Wall -Wextra -Werror

INCLUDE_DIR := .
SRC_DIRS := .
BUILD_DIR := ./build
# BONUS_DIRS := .
LIBFTDIR := ./libft

LIBFT := $(LIBFTDIR)/libft.a
INCLUDE := $(INCLUDE_DIR)/fdf.h
# INCLUDE_BONUS := $(INCLUDE_DIR)/minitalk_bonus.h

SRC := fdf.c gnl.c gen_map.c drow_line.c draw_map.c state_changing.c pro_tat.c utils.c
OBJ := $(SRC:.c=.o)
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

NAME := fdf

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME)

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