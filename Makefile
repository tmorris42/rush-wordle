NAME = wordle

SRCS_DIR = src/
INCLUDE_DIR = include/
OBJS_DIR = objs/

SRCS = main.cpp \
	guess.cpp

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))
INCLUDES = -I$(INCLUDE_DIR)
DEPS = $(OBJS:.o=.d)

CC	= c++
FLAGS = -MMD -Wall -Wextra -Werror

DEBUG_FLAGS ?= -g3
ifdef DEBUG_OVERRIDE
FLAGS := $(FLAGS) $(DEBUG_FLAGS)
endif

$(NAME): $(OBJS) | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

all: $(NAME) $(REAL)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp | $(OBJS_DIR)
	$(CC) $(MY_FLAGS) -c $(INCLUDES) $< -o $@

real: $(REAL) | $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(REAL)

re: fclean
	$(MAKE)

test: all

leaks: $(NAME)

-include $(DEPS)

.PHONY: all clean fclean re test leaks
