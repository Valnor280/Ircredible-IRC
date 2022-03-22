NAME = Ircredible

CC = c++
DEBUG_FLAG = -g -Wfatal-errors -Wpedantic -Wconversion -Wshadow
CC_FLAGS = -Wall -Wextra -Werror -std=c++98 # ${DEBUG_FLAG}


SRCS =	main.cpp \
		SERVER/server.cpp \
		SERVER/accept.cpp \
		SERVER/user_read.cpp \
		USER/user.cpp \
		COMMANDS/commands.cpp


OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I .# -I SERVER/ -I USER/

all				: 	${NAME}
$(NAME) 		: 	$(OBJS)	
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) $^ -o $@
						@echo Compiling...
-include $(DEP)
$(OBJS_DIR)/%.o	:	%.cpp
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@




clean	:
				@rm -rf $(OBJS_DIR) 
fclean	:	clean
				@rm -rf ${NAME}  
			@echo fclean
re		:	fclean
				@make all

.PHONY : all clean fclean re test
