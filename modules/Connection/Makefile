NAME_PRE=	libPreConnection.so

NAME_POST=	libPostConnection.so

DIR_SRC=	sources/

SRC_PRE=	$(DIR_SRC)PreConnection.cpp \

SRC_POST=	$(DIR_SRC)PostConnection.cpp \

OBJ_PRE=	$(SRC_PRE:.cpp=.o)

OBJ_POST=	$(SRC_POST:.cpp=.o)

CC=		g++

RM=		rm -f

CPPFLAGS=	-I./includes/ -I../../includes/ -W -Wall -Wextra -fPIC -shared

all:		$(NAME_PRE) $(NAME_POST)

$(NAME_PRE):	$(OBJ_PRE)
		$(CC) $(OBJ_PRE) -fPIC -shared -o $(NAME_PRE)

$(NAME_POST):	$(OBJ_POST)
		$(CC) $(OBJ_POST) -fPIC -shared -o $(NAME_POST)

clean:
		$(RM) $(OBJ_PRE)
		$(RM) $(OBJ_POST)

fclean:		clean
		$(RM) $(NAME_PRE)
		$(RM) $(NAME_POST)


re:		fclean all