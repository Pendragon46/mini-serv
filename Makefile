SRCS = main.cpp MiniServ.cpp

OBJ_DIR = obj

OBJ = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I . -std=c++98

NAME = MiniServ

$(OBJ_DIR)/%.o :	%.cpp
					mkdir -p $(OBJ_DIR)
					$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) :	$(OBJ)
			$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
			rm -rf $(OBJ_DIR)

fclean :	clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all re clean fclean
