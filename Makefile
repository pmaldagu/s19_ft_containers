CXX = clang++

NAME = school.out

MYNAME = my.out

SRCS = main.cpp \
		mymain.cpp

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJS = ${SRCS:.cpp=.o}

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) main.o -o $(NAME)
	$(CXX) $(CXXFLAGS) mymain.o -o $(MYNAME)
	
clean :
	$(RM) $(OBJS) $(MYOBJS)

fclean : clean
	$(RM) $(NAME) $(MYNAME)

re : fclean all

.PHONY: re fclean clean
