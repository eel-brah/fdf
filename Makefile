CC := cc
CFLAGS := -Wall -Wextra -Werror

OS := $(shell uname)

ifeq ($(OS), Darwin)  # macOS
	MLX_FLAGS := -lmlx -framework OpenGL -framework AppKit
	INCLUDE_DIR := ./include_macos
	MLX_LIB := ./minilibx_opengl
	CFLAGS += -D OS_MAC
else  # Linux
	MLX_FLAGS := -Lminilibx-linux -lmlx -lX11 -lXext -lm
	INCLUDE_DIR := ./include
	MLX_LIB := ./minilibx-linux
	CFLAGS += -D OS_LINUX
endif

SRC_DIRS := ./src
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
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
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
	@echo "\033[0;34mCompiling \033[1;34mminilibx"
	@$(MAKE) -C $(MLX_LIB)

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(MAKE) clean -C $(MLX_LIB)
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -rf $(NAME) $(BUILD_DIR)

re: fclean all

DOCKER_IMAGE := fdf:0.1

build-docker:
	@docker build -t $(DOCKER_IMAGE) .

run-docker: build-docker
	@docker run -it --rm \
		-e DISPLAY=$(DISPLAY) \
		-v /tmp/.X11-unix:/tmp/.X11-unix \
		$(DOCKER_IMAGE)

.PHONY: all clean fclean re lib build-docker run-docker
