NAME=		zia

DIR_SRC=	./sources/

SRC=		$(DIR_SRC)main.cpp \

OBJ=		$(SRC:.cpp=.o)

CC=		g++

RM=		rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all