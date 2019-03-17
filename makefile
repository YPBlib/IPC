CC=gcc
CXX = g++

C_FLAGS = -lpthread -std=c99

CXX_FLAGS = -lpthread -std=c++11
#SRCS := $(wildcard *.cpp)
#将SRCS中后缀.cpp替换成空，即可执行程序的名字与cpp名字相同
#TARGET  := $(patsubst %.cpp, %, $(SRCS))
#OBJDIR = .
server:	server/server.cpp
	$(CXX) -I. $(CXX_FLAGS) server/server.cpp -o ./s.out
client:	client/client.cpp
	$(CXX) -I. $(CXX_FLAGS) client/client.cpp -o ./c.out
pipe:	pipe.c
	 $(CC) pipe.c -o pipe.out
rdfifo.out:	rdfifo.c
	 $(CC) $(C_FLAGS) rdfifo.c -o rdfifo.out
wrfifo.out:	wrfifo.c
	 $(CC) $(C_FLAGS) wrfifo.c -o wrfifo.out


#all: $(TARGET)
clean:
	rm -rf *.o $(TARGET)


