NAME	= cTVScript_compiler

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes
########################
#### MAIN
MAIN	= src/first.cpp
### ARCHI
ARCHI_D	= src/architecture/
ARCHI	= $(ARCHI_D)line.cpp
########################
SRC	=  $(MAIN) $(ARCHI)

FLAGS	= -W -Wall -Wextra $(INC) -std=c++0x

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
