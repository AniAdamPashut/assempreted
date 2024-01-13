.SUFFIXES:
CC = g++ -std=c++20
SRC = ./src
LANG = cpp
MAIN_EXEC = assempreter
BUILD = ./build
SUB_HEADER_DIRS = $(shell find headers -type d)
HEADER_PREFIX = -I
CFLAGS = -I$(BUILD)/libs/headers $(addprefix $(HEADER_PREFIX), $(SUB_HEADER_DIRS)) -fPIC -p
LIBS = $(wildcard $(BUILD)/libs/objs/*.so)
SUBDIRS = $(shell find $(SRC) -type d)
FILES = $(wildcard $(addsuffix /*.$(LANG),$(SUBDIRS)))
OBJS = $(patsubst $(SRC)/%.$(LANG), $(BUILD)/objs/%.o, $(FILES))
ALL_OBJS = $(LIBS) $(OBJS)

all: $(MAIN_EXEC)

debug:
	make CFLAGS='$(CFLAGS) -Wall -Wextra -g'

release:
	make CFLAGS='$(CFLAGS) -O3'

lib: lib_target

lib_target: $(MAIN_EXEC).so

$(MAIN_EXEC): $(ALL_OBJS)
	$(CC) $(ALL_OBJS) -o $@

$(BUILD)/objs/%.o: $(SRC)/%.$(LANG)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_EXEC).so: $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) -shared -o $@

clean:
	rm -rf $(OBJS) $(MAIN_EXEC) $(MAIN_EXEC).so

init:
	@mkdir -p $(BUILD)/libs/headers
	@mkdir -p $(BUILD)/libs/objs
	@mkdir -p $(BUILD)/objs

.PHONY: all clean lib release debug init