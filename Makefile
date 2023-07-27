NAME=pong_server
CC=g++
FLAGS=-w
INCLUDE=-I./src

_SRC=main.cpp server.cpp tcpstream.cpp client.cpp utils.cpp game.cpp
_OBJ=$(_SRC:.cpp=.o)
_INC=def.hpp server.hpp tcpstream.hpp client.hpp
SDIR=./src/
ODIR=./obj/
IDIR=./src/
SRC=$(addprefix $(SDIR), $(_SRC))
OBJ=$(addprefix $(ODIR), $(_OBJ))
INC=$(addprefix $(IDIR), $(_INC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $(OBJ)

$(ODIR)%.o: $(SDIR)%.cpp $(INC)
	$(CC) $(INCLUDE) -c $< -o $@

.PHONY: clean re test
clean:
	rm -f $(ODIR)*.o $(NAME)

re: clean all

test:
	./$(NAME)
