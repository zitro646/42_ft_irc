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

PORT		= 6667
IP			= 127.0.0.1
PASS		= pass
CC 			= c++
INCLUDE 	= -std=c++98
CXXFLAGS 	= -Wall -Wextra -Werror

# PATHs #
#
SRC_PATH    	= srcs
SUBFILE1_PATH   = server
SUBFILE2_PATH   = server_objects
SUBFILE4_PATH   = general
SUBFILE3_PATH   = command
OBJ_PATH    	= objects
TEST_PATH		= test

# SOURCES #

SUBFILE1_SRC = server.cpp server_comm.cpp server_utilities.cpp manage_fds.cpp

SUBFILE2_SRC = client.cpp channel.cpp

SUBFILE3_SRC = join.cpp list.cpp msg.cpp nick.cpp part.cpp pong.cpp quit.cpp user.cpp\
				operator.cpp kill.cpp topic.cpp notice.cpp names.cpp kick.cpp invite.cpp\
				restart.cpp mode.cpp

SUBFILE4_SRC = aux_functions.cpp check_input_data.cpp socket_set_up.cpp

SRC =	main.cpp \
		$(addprefix $(SUBFILE3_PATH)/, $(SUBFILE3_SRC)) \
		$(addprefix $(SUBFILE2_PATH)/, $(SUBFILE2_SRC)) \
		$(addprefix $(SUBFILE4_PATH)/, $(SUBFILE4_SRC)) \
		$(addprefix $(SUBFILE1_PATH)/, $(SUBFILE1_SRC)) \



# RULES #
all: $(NAME)

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS =  $(addprefix $(OBJ_PATH)/, $(SRC:%.cpp=%.o))



$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE1_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE2_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE4_PATH))
	mkdir -p $(addprefix $(OBJ_PATH)/, $(SUBFILE3_PATH))


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

launch: all
	clear
	./$(NAME) $(IP):$(PORT):$(PASS) $(PORT) $(PASS)

PHONY.: all clean fclean re launch
