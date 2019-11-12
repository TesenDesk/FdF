# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 18:21:00 by ftothmur          #+#    #+#              #
#    Updated: 2019/11/06 14:32:06 by ftothmur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================COLORS & Co===================================#
GREEN =		\033[1;32m
RED =		\033[1;31m
RST =		\033[0m
BOLD =		\033[1m
CYAN =		\033[1;36m
PREFIX =	[$(CYAN)lem-in$(RST)]:\t

#====================================LIB=======================================#
#---------------------------------directories----------------------------------#
LIB_DIR			:=	./libft/
HL_DIR			:=	$(LIB_DIR)
#MHL_DIR			:=	..//Users/ftothmur/student21/002_0_libft/libft_currmst/libft_t/includes/
#---------------------------------ftothmur lib---------------------------------#
LIB				:=	$(LIB_DIR)libft.a
#===================================PROJECT====================================#
#---------------------------------directories----------------------------------#
MAIN_DIR		:=	./main/
HEADER_DIR		:=	./includes/
JJH_DIR			:=	./includes/
DIR				:=	./parser/
JJ_DIR			:=	./path_finder/
A_LENGTH_DIR	:=	./path_selector/
PRINT_MOVES_DIR	:=	./printer/
OBJ_DIR			:=	$(DIR)
SRC_DIR			:=	$(DIR)
#------------------------------------files-------------------------------------#
NAME			:=	lem-in
J_SRC			:=	$(addprefix $(JJ_DIR),algorithm.c bfs.c sbfs.c \
ways_manipulations.c deep_research.c recursive_research.c debug_print.c \
other_funcs.c recursive_addons.c deep_addons.c print_line.c \
staff_for_bfs_and_other.c)
F_SRC			:=	$(addprefix $(SRC_DIR),allocate_and_delete_aux_names.c \
dispatch_parsing_and_filling.c filling_edges.c find_vertex.c \
map_creation_and_filling.c checking_line_condition.c filling.c \
filling_errors_and_skips.c map_creation.c parsing.c \
allocate_and_delete_graph.c fill_ants_and_nbr_field.c \
hash_table_operations.c hash_table_allocate_delete.c)
A_LENGTH_SRC	:=	$(addprefix $(A_LENGTH_DIR),answer_length.c \
path_calculations.c path_nodes_wrapers.c \
find_largest_permitted_path.c count_steps.c path_iteration_wrapers.c \
determine_flow.c)
PRINT_MOVES		:=	$(addprefix $(PRINT_MOVES_DIR),move_ants_and_print.c \
print_common_case.c printing_manager_and_special_case.c wrapers.c)
MAIN_SRC		:=	$(addprefix $(MAIN_DIR),delete_project.c \
error_help_usage.c main_initializer.c process_arguments.c)
SRC				:=	$(MAIN_SRC) $(A_LENGTH_SRC) $(PRINT_MOVES) $(F_SRC) $(J_SRC)
OBJ				:=	$(patsubst %.c,%.o, $(SRC))
NAME_HDR_DIR	:=	$(MAIN_DIR)includes/
#----------------------------------includes------------------------------------#
LIB_HEADER		:=	$(HL_DIR)libft.h
NAME_HDR		:=	$(HEADER_DIR)ftothmur.h
JJH_HDR			:= 	$(HEADER_DIR)lemin_my.h
HEADERS			:=	$(LIB_HEADER) $(NAME_HDR) $(JJ_HDR)

#------------------------------------flags-------------------------------------#
ifeq ($(DEBUG), 1)
	CFLAGS		:=	-Wall -Wextra -Werror -g
	DEBUGMSG	:= $(PREFIX)⚠️  \033[1;33mDebug mode $(GREEN)enabled.$(RST)\n
else
	CFLAGS		:=	-Wall -Wextra -Werror
	DEBUGMSG	:= $(PREFIX)⚠️  \033[1;33mDebug mode $(RED)disabled.$(RST)\n
endif
LIB_FLAGS		:=	-L$(LIB_DIR) -lft
HDR_FLAGS		:=	-I$(JJH_DIR) -I$(NAME_HDR_DIR) -I$(HL_DIR)
#===================================RULES======================================#
all:				lib $(NAME)
				@echo "$(PREFIX)✅  $(GREEN)All files up-to-date or \
rebuilded.$(RST)"

$(NAME):			$(SRC) $(OBJ) $(HEADERS) $(LIB)
				@printf "%-145c\r$(PREFIX)✅  $(GREEN)All \
obj-files accepted.$(RST)\n" ' '
				@printf "$(PREFIX)📦  Building lem-in...\n"
				@gcc -o $(NAME) $(OBJ) $(HDR_FLAGS) $(LIB_FLAGS) $(CFLAGS)

$(LIB):				lib

lib:
				@printf "$(DEBUGMSG)$(PREFIX)$(BOLD)🔎  Checkig \
for libft updates...$(RST)\n"
				@make -C $(LIB_DIR) DEBUG=$(DEBUG)

%.o:				%.c
				@printf "%-145c\r$(PREFIX)🕐  Compiling file:\t \
%-25s=>\t%-25s\r" ' ' "$<" "$@"
				@gcc $(CFLAGS) -c $< $(HDR_FLAGS) -o $@

clean_lib:
				@make clean -C $(LIB_DIR)

clean_this:
				@rm -rf $(OBJ)
				@echo "$(PREFIX)♻️  $(RED)Removing obj-files...$(RST)"

clean: 				clean_lib clean_this

fclean_lib:
				@make fclean -C $(LIB_DIR)

fclean_this:
				@rm -rf $(NAME)
				@echo "$(PREFIX)♻️  $(RED)Removing executable file...$(RST)"

fclean:				fclean_lib clean_this fclean_this

re_lib:
				make re -C $(LIB_DIR) DEBUG=$(DEBUG)

re_this:			fclean_this all

re:					fclean all

.PHONY:			all clean  fclean re \
clean_this fclean_this \
lib clean_lib fclean_lib
