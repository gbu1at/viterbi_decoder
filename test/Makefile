CXXFLAGS = -O2 -Wall -Wextra -Werror -std=c++17 -I../include
SRCS = ../src/ViterbiDecoder.cpp ../src/ViterbiEncoder.cpp test.cpp
OBJS = $(notdir $(SRCS:.cpp=.o))
VPATH = ../src:.

all: test

test: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) test

.PHONY: all clean