CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC_DIRS := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
LIBFTDIR := ./libft

LIBFT := $(LIBFTDIR)/libft.a
INCLUDE := fdf.h fdf_keys.h
INCLUDE := $(addprefix $(INCLUDE_DIR)/,$(INCLUDE))

SRC := fdf.c gnl.c gen_map.c gen_map_utils_1.c gen_map_utils_2.c draw_line.c draw_map.c \
		state_changing_0.c state_changing_1.c projection.c utils_1.c utils_2.c gradient.c \
		draw_menu.c
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

NAME := fdf

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INCLUDE)
	@$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit $(LIBFT) -o $(NAME)
	@echo "\033[1;34m$(NAME) \033[0;34mhas been compiled"

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@[ -d "$(BUILD_DIR)" ] || mkdir "$(BUILD_DIR)"
	@echo "\033[1;34m"
	@echo "███████╗██████╗ ███████╗"
	@echo "██╔════╝██╔══██╗██╔════╝"
	@echo "█████╗  ██║  ██║█████╗  "
	@echo "██╔══╝  ██║  ██║██╔══╝  "
	@echo "██║     ██████╔╝██║     "
	@echo "╚═╝     ╚═════╝ ╚═╝     "
	@echo "\033[0m"
	@$(MAKE) -C $(LIBFTDIR)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -rf $(NAME) $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re lib