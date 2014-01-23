NAME=		zia

DIR_SRC=	./sources/

SRC=		$(DIR_SRC)main.cpp \
		$(DIR_SRC)ConfParser.cpp \
		$(DIR_SRC)Logger.cpp \
		$(DIR_SRC)Server.cpp \
		$(DIR_SRC)ModuleLoader.cpp \

OBJ=		$(SRC:.cpp=.o)

CC=		g++

RM=		rm -f

CPPFLAGS=	-I./includes/ -Wall -Wextra

LIBS=		-ldl

all:		$(MODULES) $(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LIBS)
		$(MAKE) -C ./modules/Connexion
		$(MAKE) -C ./modules/GenerateResponse
		$(MAKE) -C ./modules/GetContent
		$(MAKE) -C ./modules/ParseRequest
		$(MAKE) -C ./modules/SendResponse

clean:
		$(RM) $(OBJ)
		$(MAKE) -C ./modules/Connexion clean
		$(MAKE) -C ./modules/GenerateResponse clean
		$(MAKE) -C ./modules/GetContent clean
		$(MAKE) -C ./modules/ParseRequest clean
		$(MAKE) -C ./modules/SendResponse clean

fclean:		clean
		$(RM) $(NAME)
		$(MAKE) -C ./modules/Connexion fclean
		$(MAKE) -C ./modules/GenerateResponse fclean
		$(MAKE) -C ./modules/GetContent fclean
		$(MAKE) -C ./modules/ParseRequest fclean
		$(MAKE) -C ./modules/SendResponse fclean

re:		fclean all