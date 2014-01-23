NAME=		libGenRes.so

DIR_SRC=	sources/

SRC=		$(DIR_SRC)CgiModule.cpp \
		$(DIR_SRC)GenRes.cpp \
		$(DIR_SRC)PostGenRes.cpp \

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