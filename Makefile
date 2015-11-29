CXX = g++
CXXFLAGS = -std=c++11

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CXX = clang++
	CXXFLAGS += -stdlib=libc++
endif

all: example

example: bind-tuple.hpp example.cpp
	$(CXX) $(CXXFLAGS) -o example example.cpp

clean:
	rm -vf example;
