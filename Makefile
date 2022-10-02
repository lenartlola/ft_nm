NAME = ft_nm

SHELL = /bin/sh
CFLAGS := ${CFLAGS}

SRC_DIRS ?= ./src
INC_DIRS ?= ./incs
BUILD_DIR ?= ./build

MAKEFLAGS += --output-sync=target
MAKEFLAGS += --no-print-directory

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_FLAGS := -Ilibs/libft/incs
LIBS := -Llibs/libft -lft
LIB := libs/libft/libft.a

INC_FLAGS += $(addprefix -I,$(INC_DIRS))
CFLAGS += -Wall -Wextra -Werror
CC ?= gcc
LD ?= gcc

TEST_SRC = test/main.c

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	NPROC := $(shell nproc)
else
	NPROC := $(shell sysctl -n hw.ncpu)
endif

all:
	@$(MAKE) $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo Linking $@
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIB):
	@$(MAKE) -C libs/libft
	@echo Libft done

$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling $@
	@mkdir -p $(dir $@)
	@$(CC) -c  $(CFLAGS) $(INC_FLAGS) $< -o $@

test:
	@$(CC) $(TEST_SRC) -o simple

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) -C libs/libft clean
	@echo Clean done

fclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C libs/libft fclean
	@rm -f simple
	@echo Fclean done

re: fclean
	@$(MAKE) -j$(NPROC) $(NAME)

.PHONY: all test clean fclean re