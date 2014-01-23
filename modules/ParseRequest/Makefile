NAME=		libParseRequest.so

DIR_SRC=	sources/

SRC=		$(DIR_SRC)PreParseRequest.cpp \
		$(DIR_SRC)PostParseRequest.cpp \
		$(DIR_SRC)ParseRequest.cpp \

OBJ=		$(SRC:.cpp=.o)

CC=		g++

RM=		rm -f

CPPFLAGS=	-I./includes/ -I../../includes/ -W -Wall -Wextra -fPIC -shared

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -fPIC -shared -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)


re:		fclean all