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

FLAGS	= -W -Wall -Wextra $(INC) -std=c++0x

CFLAGS	+= $(FLAGS)
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
