CC=gcc
CXX = g++

C_FLAGS = -lpthread 

#SRCS := $(wildcard *.cpp)
#将SRCS中后缀.cpp替换成空，即可执行程序的名字与cpp名字相同
#TARGET  := $(patsubst %.cpp, %, $(SRCS))
#OBJDIR = .
server:	server/server.cpp
	$(CXX) -std=c++11 server/server.cpp  -I. $(C_FLAGS) -o ./s.out
client:	client/client.cpp
	$(CXX) -std=c++11 client/client.cpp -I. $(C_FLAGS) -o ./c.out
pipe:	pipe.c
	 $(CC) pipe.c -o pipe.out


#all: $(TARGET)
clean:
	rm -rf *.o $(TARGET)


