NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

# LIBS_DIR = libs
OBJS_DIR = objs
SRC_OBJS_DIR = $(OBJS_DIR)

# ------- Mandatory -------
SRC_HEADER_FILES = philo.h
SRC_HEADER = $(SRC_HEADER_FILES)
SRC_FILES = utils.c states.c states_update1.c states_update2.c simulation.c parsing.c lnk_list.c philo_config.c philo.c main.c
# SRC_FILES = utils.c parsing.c lnk_list.c philo.c
SRCS = $(SRC_FILES)
OBJ_FILES = $(SRCS:.c=.o)  # creates .o file names as .c, does not compile
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ_FILES))

# --------- Functions -----------
# ===Colors===
PURPLE	= \033[95m
GREEN		= \033[92m
RED 		= \033[91m
YELLOW	= \033[33m
RESET		= \033[0m

define print_green
	@printf "$(GREEN)$(1)\n$(RESET)"
endef

define print_red
	@printf "$(RED)$(1)\n$(RESET)"
endef

# --------- Rules ---------
all: $(NAME)

# .o files compilation happens in this rule
$(SRC_OBJS_DIR)/%.o: %.c  $(SRC_HEADER)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(call print_green,Compiling Mandatory ...)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# -------- Phonies --------
clean:
	$(call print_red,Cleaning Objects ...)
	@rm -rf $(OBJS_DIR)

fclean: clean
	$(call print_red,Cleaning Objects & Executables ...)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
