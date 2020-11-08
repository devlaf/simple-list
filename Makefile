################################################################################
# simple-list makefile
#
# To use:
# - Specify a LIST_LIB_OUTPUT_FILEPATH override
# - Include this makefile in your own, and specify a build_list prerequisite
#
################################################################################

LIST_LIB_MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
LIST_LIB_BUILD_DIR = $(LIST_LIB_MAKEFILE_DIR)build

ifndef LIST_LIB_OUTPUT_FILEPATH
  LIST_LIB_OUTPUT_FILEPATH := $(LIST_LIB_BUILD_DIR)/list.a
endif

LIST_LIB_CXX       = gcc
LIST_LIB_CFLAGS    = -Wall

LIST_LIB_INCLUDES = $(LIST_LIB_MAKEFILE_DIR)include
LIST_LIB_SOURCES  = $(LIST_LIB_MAKEFILE_DIR)src/linked_list.c 

build_list:
	mkdir -p $(LIST_LIB_BUILD_DIR);
	mkdir -p $(dir $(LIST_LIB_OUTPUT_FILEPATH));
	$(LIST_LIB_CXX) -Os -c $(LIST_LIB_SOURCES) -I $(LIST_LIB_INCLUDES) $(LIST_LIB_CFLAGS) -o $(LIST_LIB_BUILD_DIR)/list.o;
	ar rcs $(LIST_LIB_OUTPUT_FILEPATH) $(LIST_LIB_BUILD_DIR)/list.o;

clean_list:
	rm -f $(LIST_LIB_BUILD_DIR)/list.o;
	rm -f $(LIST_LIB_OUTPUT_FILEPATH);
