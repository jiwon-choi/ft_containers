TARGET		= ft_containers

CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98
RM			= rm -rf

SRCS		= test.cpp

OBJS		= $(SRCS:.cpp=.o)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all : $(TARGET)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(TARGET)

re : clean all

bonus :

.PHONY : all clean fclean re bonus
