# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flogan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/10 21:07:00 by flogan            #+#    #+#              #
#    Updated: 2019/11/11 15:21:45 by flogan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LEM_IN =		lem-in
VISUAL =		visu-hex
NAME =			$(LEM_IN) $(VISUAL)
LIBFT_A =		libftprintf.a
KEY =  -framework OpenGL -L/Users/flogan/.brew/lib -lSDL2 -I/Users/flogan/.brew/include/SDL2 -D_THREAD_SAFE -lSDL2_image

COMP =			gcc -Wall -Wextra -Werror -Wno-deprecated-declarations -g -I include -I ft_printf/include -c -o

OBJ_DIR =		obj/
S_SRC_DIR =		share/
L_SRC_DIR =		lem_in/
V_SRC_DIR =		visualisation/
LIBFT =			ft_printf/

S_SRC =			help_function.c \
				list_methods.c \
				parser.c \
				valid.c \


L_SRC =			algorithm.c \
				djkstra_function.c \
				freez.c \
				main.c \
				print_alg.c \
				search_path.c \
				work_with_matrix.c \

V_SRC =			main_visual.c \
                parsers.c \
                print_graph_ants.c \
                run_ants.c \
                start_vis.c \
                list_method_vis.c \

S_OBJ =			$(S_SRC:%.c=%.o)
L_OBJ =			$(L_SRC:%.c=%.o)
V_OBJ =			$(V_SRC:%.c=%.o)

OBJ =			$(S_OBJ) $(V_OBJ) $(L_OBJ)

S_SRC_PATH =   	$(S_SRC:%=$(S_SRC_DIR)%)
L_SRC_PATH =   	$(L_SRC:%=$(L_SRC_DIR)%)
V_SRC_PATH =   	$(V_SRC:%=$(V_SRC_DIR)%)
SRC_PATH =		$(S_SRC_PATH) $(L_SRC_PATH) $(V_SRC_PATH)

S_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(S_OBJ))
L_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(L_OBJ))
V_OBJ_PATH =	$(addprefix $(OBJ_DIR), $(V_OBJ))
OBJ_PATH =		$(S_OBJ_PATH) $(L_OBJ_PATH) $(V_OBJ_PATH)

all:			color do_libft $(OBJ_DIR) $(NAME)
				@echo "\\n"DONE"\\n"

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)
				@echo Create: Object directory

$(NAME):		$(OBJ_PATH)
				@gcc $(S_OBJ_PATH) $(L_OBJ_PATH) *.a -o $(LEM_IN) \
					-I include -I $(LIBFT)include
				@gcc $(S_OBJ_PATH) $(V_OBJ_PATH) *.a -o $(VISUAL) \
					-I include -I$(LIBFT)include $(KEY)

$(S_OBJ_PATH):	$(S_SRC_PATH)
				@$(MAKE) $(S_OBJ)

$(L_OBJ_PATH):	$(L_SRC_PATH)
				@$(MAKE) $(L_OBJ)

$(V_OBJ_PATH):	$(V_SRC_PATH)
				@$(MAKE) $(V_OBJ)

$(S_OBJ):		$(LIBFT_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(S_SRC_DIR)$(@:%.o=%.c)
$(V_OBJ):		$(LIBFT_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(V_SRC_DIR)$(@:%.o=%.c)
$(L_OBJ):		$(LIBFT_A)
				@echo Create: $(@:obj/%=%)"\x1b[1A\x1b[M"
				@$(COMP) $(OBJ_DIR)$@ $(L_SRC_DIR)$(@:%.o=%.c)

do_libft:
				@make -C $(LIBFT)
				@cp $(LIBFT)/$(LIBFT_A) .

color:
				@echo "\x1b[36m""\x1b[1A\x1b[M"

clean:			color
				@/bin/rm -rf $(OBJ_DIR) $(FT_PRINTF_A) $(LIBFT_A)
				@make -C $(LIBFT) clean
				@echo Cleaned libft object files

fclean:			clean
				@/bin/rm -f $(LEM_IN) $(VISUAL) $(FT_PRINTF_A) $(LIBFT_A)
				@make -C $(LIBFT) fclean
				@echo Cleaned $(NAME)

re: 			fclean all

.PHONY:			all clean flcean re color
