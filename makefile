# helper functions
eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))

# path setting
PROJECT := minilibc
INCLUDE_DIR := include
SOURCE_DIR := src
EXAMPLE_DIR := examples
LIBTYPE := static

STATIC_LIB := lib$(PROJECT).a
DYNAMIC_LIB := lib$(PROJECT).so
#  -Wl,-rpath ./
LIBNAME = $(if $(call eq,$(LIBTYPE),static),$(STATIC_LIB),$(DYNAMIC_LIB))
$(info Build LIB name is $(LIBNAME))

BUILD_DIR := ./build
OBJS_OUTPUT_DIR := $(BUILD_DIR)/objects
LIBS_OUTPUT_DIR := $(BUILD_DIR)/libraries
EXAMPLES_OUTPUT_DIR := $(BUILD_DIR)/examples

# compiler options
CC := gcc
CFLAGS := -fno-builtin -nostdlib -fno-stack-protector
CFLAGS += -I$(INCLUDE_DIR)

LDFLAGS = $(if $(call eq,$(LIBTYPE),static),-static)
CODE_GENERATE_FLAGS = $(if $(call eq,$(LIBTYPE),dynamic),-fPIC,-fno-PIC)

# primary files 
SRC := $(wildcard $(SOURCE_DIR)/*.c)
OBJS := $(patsubst %.c, $(OBJS_OUTPUT_DIR)/%.o, $(notdir $(SRC)))

# start files
START_SRC := $(SOURCE_DIR)/start/mini_start.c $(SOURCE_DIR)/start/_start.S
START_OBJS := $(OBJS_OUTPUT_DIR)/start/mini_start.o $(OBJS_OUTPUT_DIR)/start/_start.o

# provide global construct/destruct
CTOR_SRC := $(wildcard $(SOURCE_DIR)/ctors/*.c)
CTOR_OBJS := $(patsubst %.c, $(OBJS_OUTPUT_DIR)/ctors/%.o, $(notdir $(CTOR_SRC)))

# examples
EXE_SRC := $(wildcard $(EXAMPLE_DIR)/*.c)
EXE := $(patsubst %.c, $(EXAMPLES_OUTPUT_DIR)/%, $(notdir $(EXE_SRC)))


# build targets
all: dir $(START_OBJS) $(CTOR_OBJS) $(OBJS) $(LIBNAME) $(EXE)

dir:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(OBJS_OUTPUT_DIR)
	mkdir -p $(LIBS_OUTPUT_DIR)
	mkdir -p $(EXAMPLES_OUTPUT_DIR) 

$(OBJS_OUTPUT_DIR)/start/%.o: $(SOURCE_DIR)/start/%.[cS]
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_OUTPUT_DIR)/ctors/%.o: $(SOURCE_DIR)/ctors/%.[cS]
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CODE_GENERATE_FLAGS) -c $< -o $@

$(OBJS_OUTPUT_DIR)/%.o: $(SOURCE_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CODE_GENERATE_FLAGS) -c $< -o $@

$(LIBNAME): $(OBJS)
ifeq ($(LIBNAME),$(STATIC_LIB))
	ar rcs $(LIBS_OUTPUT_DIR)/$@ $(OBJS) $(CTOR_OBJS) $(START_OBJS)
else
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(LIBS_OUTPUT_DIR)/$@
endif

$(EXAMPLES_OUTPUT_DIR)/%: $(EXAMPLE_DIR)/%.c $(LIBNAME) $(START_OBJS) $(CTOR_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -L$(LIBS_OUTPUT_DIR) $< $(START_OBJS) $(CTOR_OBJS)  -l$(PROJECT)  -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)