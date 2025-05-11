CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

TARGET = tcp_echo_server
SRCS = main.cpp tcp_echo.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

.PHONY: all clean
