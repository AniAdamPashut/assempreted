.SUFFIXES:
CC = g++ -std=c++20
SRC = ./src
LANG = cpp
MAIN_EXEC = assempreter
BUILD = ./build
CFLAGS = -Iheaders -I$(BUILD)/libs/headers -fPIC
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
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_EXEC).so: $(ALL_OBJS)
	$(CC) $(CFLAGS) $(ALL_OBJS) -shared -o $@

clean:
	rm -rf $(OBJS) $(MAIN_EXEC)

.PHONY: all clean lib release debug