CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC_DIRS := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
FT_PRINTF_DIR = ft_printf
INCLUDE := $(INCLUDE_DIR)/libft.h $(INCLUDE_DIR)/ft_printf.h

FT_PRINTF_SRC_FILES := ft_printf.c ft_printf_bonus.c ft_printf_print_bonus.c ft_printf_print_ints_format_bonus.c \
ft_printf_print_ints_format_helpers.c ft_printf_print_ints_format_helpers_bonus.c \
ft_printf_print_adrs_bonus.c ft_printf_print_ints_adrs_helpers_bonus.c ft_printf_print_helpers.c \
ft_printf_print_chars_bonus.c ft_printf_format_generator_bonus.c ft_printf_format_fill_bonus.c
FT_PRINTF := $(addprefix $(FT_PRINTF_DIR)/,$(FT_PRINTF_SRC_FILES))

SRC_FILES := ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_bzero.c ft_isprint.c \
			ft_strrchr.c ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c  \
			ft_memset.c ft_strchr.c ft_strlen.c ft_substr.c ft_calloc.c ft_tolower.c ft_isalnum.c \
			ft_itoa.c ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_strncmp.c ft_toupper.c \
			ft_memchr.c ft_putendl_fd.c ft_striteri.c ft_strjoin.c ft_strnstr.c ft_isalpha.c \
			ft_memcmp.c ft_putnbr_fd.c $(FT_PRINTF) \
			ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstmap_bonus.c ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c
OBJ_FILES := $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
NAME := libft.a

all: $(BUILD_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rcs $@ $?
	@echo "\033[1;34mlibft.a \033[0;34mhas been compiled"

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@[ -d "$(BUILD_DIR)" ] || (mkdir "$(BUILD_DIR)" && echo "\033[0;34mCompiling \033[1;34mlibft.a")
	@[ -d "$(BUILD_DIR)/ft_printf" ] || mkdir "$(BUILD_DIR)/ft_printf"

clean:
	@rm -rf $(OBJ_FILES) $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus dir
