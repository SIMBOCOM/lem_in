NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -O2

LIBFT = libft

DIR_S = ft_printf

DIR_O = temporary

HEADER = include

SOURCES =	ft_printf.c\
			parsers_printf.c\
			parsers.c\
			long_arithmetic.c\
			print_float.c\
			convert_float_to_str.c\
			help_function_float.c\
			help_function_parsers.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
.PHONY: all clean fclean re norm run run_warn test rmt
