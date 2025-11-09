CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = custom_shell
SRCS = main.cpp shell.cpp parser.cpp executor.cpp job_control.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
