# Makefile

# DPDK installation path


# Compiler
CC = gcc
CXX = g++

# Compiler flags
CFLAGS = -O3 -g
CXXFLAGS = -std=c++11

# Use pkg-config to get compiler and linker flags
CFLAGS_DPDK = $(shell pkg-config --cflags libdpdk benchmark)
LDFLAGS_DPDK = $(shell pkg-config --libs libdpdk benchmark)

# Linker flags
LDFLAGS = $(LDFLAGS_DPDK)

# Include DPDK headers
INCLUDES = -I$(CFLAGS_DPDK)

# Source file
SRC ?= main.cpp

# Output binary
OUTPUT ?= my_program_MP

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CXX) $(CFLAGS) $(INCLUDES) $(SRC) $(LDFLAGS) $(CXXFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)
