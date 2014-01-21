NAME=		zia

DIR_SRC=	./sources/

SRC=		$(DIR_SRC)main.cpp \
		$(DIR_SRC)ConfParser.cpp \
		$(DIR_SRC)Logger.cpp \

OBJ=		$(SRC:.cpp=.o)

CC=		g++

RM=		rm -f

CPPFLAGS=	-I./includes/ -Wall -Wextra

LIBS=		-ldl

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIBS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all