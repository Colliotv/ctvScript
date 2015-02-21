NAME		= cTVScript_compiler
ctvDirTest	= test_ctv

CC	= g++
RM	= rm -f

SRC	=
INC	= -I ./includes
########################
#### MAIN
MAIN		= src/launch/main.cpp

#### ARCHI
ARCHI_LINE	= \
		src/architecture/line/ScopedId.cpp \
		src/architecture/line/ScopedType.cpp \
		src/architecture/line/TypeDefinition.cpp

ARCHI_NODE	= \
		src/architecture/node/type_definition.cpp


ARCHI		= src/architecture/ASTfactory.cpp \
		src/architecture/ASTlaunch.cpp \
		$(ARCHI_LINE) $(ARCHI_NODE)
### syntax
SYNTAX		= src/syntax/ASTparser.cpp\
		src/syntax/utils.cpp\
		src/syntax/dictionnary.cpp

### EXCEPTION
EXCEPTION	= src/exception/syntax.cpp

### DATA
DATA		= src/data/derived_types.cpp

########################
SRC	=  $(MAIN) $(SYNTAX) $(ARCHI) $(EXCEPTION) $(DATA)

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
