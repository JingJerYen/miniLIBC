# path setting
PROJECT := minilibc
INCLUDE_DIR := include
SOURCE_DIR := src
EXAMPLE_DIR := examples
STATIC_LIB = lib$(PROJECT).a
DYNAMIC_LIB = lib$(PROJECT).so

BUILD_DIR := build
OBJS_OUTPUT_DIR := $(BUILD_DIR)/objects
LIBS_OUTPUT_DIR := $(BUILD_DIR)/libraries
EXAMPLES_OUTPUT_DIR := $(BUILD_DIR)/examples

# compiler options
CC := gcc
CFLAGS := -fno-builtin -nostdlib -fno-stack-protector
CFLAGS += -I$(INCLUDE_DIR)
LDFLAGS := -static

# pattern match
SRC := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(patsubst %.c, $(OBJS_OUTPUT_DIR)/%.o, $(notdir $(SRC)))

START_SRC := $(SOURCE_DIR)/start/mini_start.c $(SOURCE_DIR)/start/_start.S
START_OBJS := $(OBJS_OUTPUT_DIR)/start/mini_start.o $(OBJS_OUTPUT_DIR)/start/_start.o

EXE_SRC := $(wildcard $(EXAMPLE_DIR)/*.c)
EXE := $(patsubst %.c, $(EXAMPLES_OUTPUT_DIR)/%, $(notdir $(EXE_SRC)))

# build targets
all: dir $(START_OBJS) $(OBJS) $(STATIC_LIB) $(EXE)

dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJS_OUTPUT_DIR)
	mkdir -p $(LIBS_OUTPUT_DIR)
	mkdir -p $(EXAMPLES_OUTPUT_DIR) 

$(OBJS_OUTPUT_DIR)/start/%.o: $(SOURCE_DIR)/start/%.[cS]
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_OUTPUT_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJS) $(START_OBJS)
	ar rcs $(LIBS_OUTPUT_DIR)/$@ $(OBJS) $(START_OBJS)

$(EXAMPLES_OUTPUT_DIR)/%: $(EXAMPLE_DIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $<  $(LIBS_OUTPUT_DIR)/$(STATIC_LIB) -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) hello_world 