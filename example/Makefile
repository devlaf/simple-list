.DEFAULT_GOAL := default

export LIST_LIB_OUTPUT_FILEPATH = ./libs/list.a
BIN_PATH = ./bin

CXX               = gcc
CFLAGS            = -Wall

SOURCES  = ./src/main.c
INCLUDES = ../include
LIBS     = ./libs/list.a

include ../Makefile

default : build_list
	mkdir -p $(BIN_PATH);
	$(CXX) -I$(INCLUDES) $(CFLAGS) -o $(BIN_PATH)/test $(SOURCES) $(LIBS);

clean : clean_list
	rm -rf $(BIN_PATH);
