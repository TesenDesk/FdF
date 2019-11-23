# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftothmur <ftothmur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 18:21:00 by ftothmur          #+#    #+#              #
#    Updated: 2019/11/23 01:05:29 by ftothmur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#====================================LIB=======================================#
#---------------------------------directories----------------------------------#
LIB_DIR			:=	./libft/libft_curr/
LIB_HDR_DIR		:=	$(LIB_DIR)
#---------------------------------ftothmur lib---------------------------------#
LIB_NAME		:=	libft
LIB				:=	$(LIB_DIR)$(LIB_NAME).a
#===================================PROJECT====================================#
#---------------------------------directories----------------------------------#
NAME_DIR		:=	./
NAME_HDR_DIR	:=	./includes/
NAME_OBJ_DIR	:=	$(NAME_DIR)src/
NAME_SRC_DIR	:=	$(NAME_DIR)src/
PARSER_DIR		:=	$(NAME_SRC_DIR)parser/
DRAW_DIR		:=	$(NAME_SRC_DIR)draw/
#------------------------------------files-------------------------------------#
NAME			:=	fdf
MAIN_SRC		:=	$(addprefix $(NAME_SRC_DIR),main.c)
PARSER_SRC		:=	$(addprefix $(PARSER_DIR), parser.c)
DRAW_SRC		:=	$(addprefix $(DRAW_DIR),drawing.c)
SRC				:=	$(MAIN_SRC) $(PARSER_SRC) $(DRAW_SRC)
OBJ				:=	$(patsubst %.c,%.o, $(SRC))
#----------------------------------includes------------------------------------#
LIB_HDR			:=	$(LIB_HDR_DIR)libft.h
NAME_HDR		:=	$(NAME_HDR_DIR)fdf.h
HEADERS			:=	$(LIB_HDR) $(NAME_HDR)

#================================COLORS & Co===================================#
GREEN =		\033[1;32m
RED =		\033[1;31m
RST =		\033[0m
BOLD =		\033[1m
CYAN =		\033[1;36m
PREFIX =	[$(CYAN)$(NAME)$(RST)]:\t\t

#------------------------------------flags-------------------------------------#
ifeq ($(DEBUG), 1)
	CFLAGS		:=	-Wall -Wextra -Werror -g
	DEBUGMSG	:= $(PREFIX)⚠️  \033[1;33mDebug mode $(GREEN)enabled.$(RST)\n
else
	CFLAGS		:=	-Wall -Wextra -Werror
	DEBUGMSG	:= $(PREFIX)⚠️  \033[1;33mDebug mode $(RED)disabled.$(RST)\n
endif
MLX_FLAGS		:= -L./minilibx -lmlx  -framework OpenGL -framework AppKit
LIB_FLAGS		:=	-L$(LIB_DIR) -lft $(MLX_FLAGS)
HDR_FLAGS		:=	-I$(NAME_HDR_DIR) -I$(LIB_HDR_DIR)

#===================================RULES======================================#
all:				lib $(NAME)
				@echo "$(PREFIX)✅  $(GREEN)All files up-to-date or \
rebuilded.$(RST)"

$(NAME):			$(SRC) $(OBJ) $(HEADERS) $(LIB)
				@printf "%-145c\r$(PREFIX)✅  $(GREEN)All \
obj-files accepted.$(RST)\n" ' '
				@printf "$(PREFIX)📦  Building $(NAME)...\n"
#				@gcc -o $(NAME) $(OBJ) $(HDR_FLAGS) $(LIB_FLAGS) $(CFLAGS)
				cc -o $(NAME) $(SRC) $(HDR_FLAGS) $(LIB_FLAGS)i -g

$(LIB):				lib

lib:
				@printf "$(DEBUGMSG)$(PREFIX)$(BOLD)🔎  Checkig \
for $(LIB_NAME) updates...$(RST)\n"
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
