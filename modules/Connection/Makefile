NAME=		libConnection.so

DIR_SRC=	sources/

SRC=		$(DIR_SRC)PreConnection.cpp \
		$(DIR_SRC)PostConnection.cpp \
		$(DIR_SRC)Connection.cpp \

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