FT					= ft
STD					= std

CXX					= c++
CXXFLAGS		= -Wall -Werror -Wextra -std=c++98
RM					= rm -rf

OBJS_DIR		= ./objs/

FT_SRCS			= ft.cpp
STD_SRCS		= std.cpp
FT_OBJS			= $(addprefix $(OBJS_DIR), $(FT_SRCS:.cpp=.o))
STD_OBJS		= $(addprefix $(OBJS_DIR), $(STD_SRCS:.cpp=.o))

all : $(FT) $(STD)

$(FT) : $(FT_OBJS)
	$(CXX) -o $(FT) $(FT_OBJS)

$(STD) : $(STD_OBJS)
	$(CXX) -o $(STD) $(STD_OBJS)

$(OBJS_DIR)%.o : %.cpp
	@mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

clean :
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(FT) $(STD)

re : clean all

bonus :

.PHONY : all clean fclean re bonus