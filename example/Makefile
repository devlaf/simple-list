.DEFAULT_GOAL := default

export LIST_LIB_OUTPUT_FILEPATH = ./libs/list.a
BIN_PATH = ./bin

LINUX_CXX               = gcc
LINUX_CFLAGS            = -Wall

SOURCES  = ./src/main.c
INCLUDES = ../include
LIBS     = ./libs/list.a

include ../Makefile

default : build_list
	mkdir -p $(BIN_PATH);
	$(LINUX_CXX) -I$(INCLUDES) $(LINUX_CFLAGS) -o $(BIN_PATH)/test $(SOURCES) $(LIBS);

clean : clean_list
	rm -rf $(BIN_PATH);
