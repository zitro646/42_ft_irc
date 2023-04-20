# COLORS #
#
GREEN 	= @echo "\033[0;32m"
BLUE 	= @echo "\033[0;34m" 
PURPLE 	= @echo "\033[0;35m"
CYAN 	= @echo "\033[0;36m"
RESET 	= "\033[1;0m"

# VARIABLES #
#
NAME 		= ircserv
CC 			= c++
INCLUDE 	= -std=c++98
CXXFLAGS 	= -Wall -Wextra -Werror

# PATHs #
#
SRC_PATH    	= srcs
SUBFILE1_PATH   = server
SUBFILE4_PATH   = general
OBJ_PATH    	= objects
TEST_PATH		= test

# SOURCES #

SUBFILE1_SRC = server.cpp server_comm.cpp server_set_up.cpp  server_utilities.cpp

SUBFILE4_SRC = aux_functions.cpp check_input_data.cpp

SRC =  	main.cpp \
		$(addprefix $(SUBFILE1_PATH)/, $(SUBFILE1_SRC)) \
		$(addprefix $(SUBFILE4_PATH)/, $(SUBFILE4_SRC)) \
		$(addprefix $(SUBFILE5_PATH)/, $(SUBFILE5_SRC)) 



# RULES #
all: $(NAME)

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(SRC:%.cpp=%.o))



$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE1_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE4_PATH))


$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
            
$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
#clear
	$(GREEN) Program asembled $(RESET)

##RULES
$(MAKE): make

clean:
	$(PURPLE) CLEANING OBJECTS $(RESET)
	rm -rf $(OBJ_PATH)
	
fclean: clean
	$(PURPLE) CLEANING DIRECTORY AND EXEC $(RESET)
	rm -rf $(NAME)
	rm -rf $(OBJ_PATH)

re: fclean all

PHONY.: all clean fclean re
