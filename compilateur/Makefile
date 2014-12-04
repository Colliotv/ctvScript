NAME		= cTVScript_compiler
ctvDirTest	= test_ctv

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes
########################
#### MAIN
MAIN	= src/first.cpp
### syntax
SYNTAX	= src/syntax/ASTparser.cpp\
	src/syntax/utils.cpp\
	src/syntax/dictionnary.cpp
########################
SRC	=  $(MAIN) $(SYNTAX)

FLAGS	= -W -Wall -Wextra $(INC) -std=c++11 -g3

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

test:
	@find $(ctvDirTest)/*.ctv -exec echo "test on {" {} "}" \; -exec ./$(NAME) {} \;

.cpp.o:
	$(CC) -c -o $@ $< $(CFLAGS)
