# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = gcc
C_STANDART = -std=c99
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Werror -Wextra

# **************************************************************************** #
# PHILO_ONE TARGET DESCRIPTION

PHILO_ONE_NAME = philo_one
PHILO_ONE_PATH = srcs
PHILO_ONE_FILE = ./philo_one
PHILO_ONE_SRCS = fill_configuration_from_args.c logging.c main.c philosopher_live.c philosopher_die.c
PHILO_ONE_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(PHILO_ONE_SRCS))
PHILO_ONE_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(PHILO_ONE_SRCS))
PHILO_ONE_LIBS = -l philo_sub -L .
PHILO_ONE_INCS = -I includes

# **************************************************************************** #
# PHILO_SUB TARGET DESCRIPTION

PHILO_SUB_NAME = philo_sub
PHILO_SUB_PATH = srcs/utilities
PHILO_SUB_FILE = ./libphilo_sub.a
PHILO_SUB_SRCS = get_current_time.c is_number.c string_len.c string_to_int.c timeval_into_size_t.c upgraded_usleep.c ft_strcpy.c numlen.c mem_help.c size_t_to_string.c
PHILO_SUB_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(PHILO_SUB_SRCS))
PHILO_SUB_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(PHILO_SUB_SRCS))
PHILO_SUB_LIBS = 
PHILO_SUB_INCS = -I includes

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all: $(PHILO_SUB_FILE) $(PHILO_ONE_FILE)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(PHILO_SUB_FILE) $(PHILO_ONE_FILE)

re: fclean all

$(PHILO_ONE_FILE): $(PHILO_SUB_FILE) $(PHILO_ONE_OBJS)
	@$(C_COMPILER) $(C_LFLAGS) $(C_STANDART) -o $(PHILO_ONE_FILE) $(PHILO_ONE_OBJS)  $(PHILO_ONE_LIBS)
	@printf 'Finished	\033[1;32m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(PHILO_ONE_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(PHILO_ONE_INCS) -o $@ -c $< -MMD

$(PHILO_SUB_FILE): $(PHILO_SUB_OBJS)
	@ar rc $(PHILO_SUB_FILE) $(PHILO_SUB_OBJS)
	@ranlib $(PHILO_SUB_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(PHILO_SUB_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(PHILO_SUB_INCS) -o $@ -c $< -MMD

-include $(PHILO_ONE_DEPS) $(PHILO_SUB_DEPS)
