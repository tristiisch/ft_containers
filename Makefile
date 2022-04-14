CXX					=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98
NAME_FT				=	test_ft
NAME_STL			=	test_stl
SRCS_DIR			=	srcs
SRCS_TEST_DIR		=	$(SRCS_DIR)/test
DEFINE_IS_STL		=	IS_STL

SRCS_TEST 			=	$(shell find $(SRCS_TEST_DIR) -type f -name '*.cpp')
INCLUDES			=	$(shell find $(SRCS_DIR) -type f -name '*.hpp')

all: $(NAME_FT) $(NAME_STL)

$(NAME_FT): $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(SRCS_TEST) -D $(DEFINE_IS_STL)=0 -o $(NAME_FT)

$(NAME_STL): $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(SRCS_TEST) -D $(DEFINE_IS_STL)=1 -o $(NAME_STL)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) -r $(NAME_FT) $(NAME_STL)

re: fclean all

.PHONY: fclean all re
.PHONY: fclean all re
