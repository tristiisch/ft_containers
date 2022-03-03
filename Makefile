CXX					=	c++
CXXFLAGS			=	-Wall -Wextra -Werror -std=c++98
NAME_FT				=	test_ft
NAME_STL			=	test_stl
SRCS_DIR			=	srcs
SRCS_TEST_DIR		=	$(SRCS_DIR)/test
OBJS_DIR			=	.objs
DEFINE_IS_STL		=	IS_STL

SRCS_TEST 			=	$(shell find $(SRCS_TEST_DIR) -type f -name '*.cpp')
INCLUDES			=	$(shell find $(SRCS_DIR) -type f -name '*.hpp')
OBJS				=	$(SRCS_TEST:$(SRCS_TEST_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME_STL) $(NAME_FT)

$(OBJS_DIR)/%.o: $(SRCS_TEST_DIR)/%.cpp $(INCLUDES)
	mkdir -p $(dir $@) && $(CXX) $(CXXFLAGS) -c -o $@ $<

$(NAME_FT): $(OBJS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(OBJS) -D $(DEFINE_IS_STL)=0 -o $(NAME_FT)

$(NAME_STL): $(OBJS) $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(OBJS) -D $(DEFINE_IS_STL)=1 -o $(NAME_STL)

clean:
	$(RM) -f $(OBJS)

fclean: clean
	$(RM) -rf $(NAME_FT) $(NAME_STL)

re: fclean all

.PHONY: fclean all re
