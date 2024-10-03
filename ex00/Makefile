# Variables
NAME        := bitwiseadd

SRCDIR      := src
OBJDIR      := object
HDRDIR      := include
HDR         := $(wildcard $(HDRDIR)/*.hpp)
INC         := -I./include

CXX         := g++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++17 #-g

SRCS        := $(wildcard $(SRCDIR)/*.cpp)
OBJS        := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS        := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.d,$(SRCS))

MKDIR       := mkdir -p
RM          := rm -rf

# Define color codes for output messages
YELLOW      := "\033[1;33m"
GREEN       := "\033[1;32m"
END         := "\033[0m"

# Declare phony targets
.PHONY: all clean fclean re test

# Default target for building the project
all: $(NAME)

# Main target
$(NAME): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo $(GREEN) "\n\tProject is compiled\n" $(END)

# Rule for generating dependency and object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HDR)
	$(MKDIR) $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

# Include generated dependency files
-include $(DEPS)

# Target for cleaning the project
clean:
	$(RM) $(OBJDIR)
	@echo $(YELLOW) "\n\tProject 'clean' status: DONE\n" $(END)

# Target for fully cleaning the project
fclean: clean
	$(RM) $(NAME)
	@echo $(YELLOW) "\n\tProject 'fclean' status: DONE\n" $(END)

# Target for rebuilding the project
re: fclean all

test:
	@echo $(YELLOW) "\nRunning tests...\n" $(END)
	./$(NAME)

