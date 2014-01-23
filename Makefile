NAME=		zia

DIR_SRC=	./sources/

SRC=		$(DIR_SRC)main.cpp \
		$(DIR_SRC)ConfParser.cpp \
		$(DIR_SRC)Logger.cpp \
		$(DIR_SRC)ModuleLoader.cpp \

OBJ=		$(SRC:.cpp=.o)

CC=		g++

RM=		rm -f

CPPFLAGS=	-I./includes/ -Wall -Wextra

LIBS=		-ldl

all:		$(MODULES) $(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIBS)
		$(MAKE) -C ./modules/Connection

clean:
		$(RM) $(OBJ)
		$(MAKE) -C ./modules/Connection clean

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) -C ./modules/Connection fclean

re:		fclean all