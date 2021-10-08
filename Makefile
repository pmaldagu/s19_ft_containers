CXX = clang++

NAME = a.out

SRCS = main.cpp 

CXXFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: re fclean clean
