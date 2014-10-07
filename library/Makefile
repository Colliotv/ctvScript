NAME	= cTVScript

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes
########################
#### MAIN
MAIN	= src/Test/main.cpp
########################
SRC	=  $(MAIN)

FLAGS	= -W -Wall -Wextra $(INC)				\
	-I lib/Gdl_lib/includes --std=c++0x -g3

CFLAGS		+= $(FLAGS)
LDFLAGS		= 

OBJ		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.cpp.o:
	$(CC) -c -o $@ $< $(CFLAGS)