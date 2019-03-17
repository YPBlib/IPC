CC = g++
C_FLAGS = -lpthread 

#SRCS := $(wildcard *.cpp)
#将SRCS中后缀.cpp替换成空，即可执行程序的名字与cpp名字相同
#TARGET  := $(patsubst %.cpp, %, $(SRCS))
#OBJDIR = .
server:
	g++ -std=c++11 server/server.cpp  -I. -lpthread -o ./s.out
client:
	g++ -std=c++11 client/client.cpp -I. -lpthread -o ./c.out



#all: $(TARGET)
clean:
	rm -rf *.o $(TARGET)


