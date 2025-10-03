CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -Iinclude

SRC = $(wildcard src/*.cpp)
TARGET = bin/tp1.exe

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	del /Q $(TARGET) 2>nul || true
