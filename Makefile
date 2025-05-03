INCLUDE_DIR := include
SRC_DIR		:= src
BIN_DIR 	:= bin

CC			:= gcc
CFLAGS		:= -O2 -I$(INCLUDE_DIR) -Wall -Wextra -Wpedantic -Werror

DEPS		:= $(INCLUDE_DIR)/common.h\
			   $(INCLUDE_DIR)/manhattan_distance_transform.h

.PHONY: help\
		all\
		IMPL_2PASS\
		IMPL_4PASS\
		clean\
		dirs

.DEFAULT_GOAL := help

help:
	@echo "Specific target required, list of available:"
	@echo "  - all"
	@$(foreach t,$(IMPLS),echo "  - $(t)";)
	@echo ""
	@echo "Usage examples:"
	@echo "  make all"
	@echo "  make IMPL_2PASS"

dirs:
	@mkdir -p $(BIN_DIR)

all: dirs $(IMPLS)

IMPL_2PASS: dirs\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/impl_2pass.c\
			$(DEPS)

	@echo "Building IMPL_2PASS..."

	@$(CC) $(CFLAGS) \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/impl_2pass.c \
	-o $(BIN_DIR)/impl_2pass

	@echo " -> output: impl_2pass"

IMPL_4PASS: dirs\
			$(SRC_DIR)/main.c\
			$(SRC_DIR)/impl_4pass.c\
			$(DEPS)

	@echo "Building IMPL_4PASS..."
	
	@$(CC) $(CFLAGS) \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/impl_4pass.c \
	-o $(BIN_DIR)/impl_4pass

	@echo " -> output: impl_4pass"


clean:
	rm -rf $(BIN_DIR)

