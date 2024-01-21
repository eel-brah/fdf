CC := cc
# CFLAGS := -Wall -Wextra -Werror

INCLUDE_DIR := include
SRC_DIRS := src
BUILD_DIR := ./build
# BONUS_DIRS := .
LIBFTDIR := ./libft

LIBFT := $(LIBFTDIR)/libft.a
INCLUDE := fdf.h
INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INCLUDE))
# INCLUDE_BONUS := $(INCLUDE_DIR)/minitalk_bonus.h

SRC := fdf.c gnl.c gen_map.c draw_line.c draw_map.c state_changing.c projection.c utils.c
SRC := $(addprefix $(SRC_DIRS)/,$(SRC))
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