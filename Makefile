NAME	=	so_long

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
FLAGS	=	-lmlx -lXext -lX11
RM		=	rm -rf

SRC_DIR	=	./src/
MLX_DIR	=	./mlx-linux/
GNL_DIR	=	./get_next_line/

SRC		=	$(SRC_DIR)main.c $(SRC_DIR)read_map.c $(SRC_DIR)put.c $(SRC_DIR)init_vars.c $(SRC_DIR)destroy_and_exit.c \
			$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
OBJ		=	$(SRC:.c=.o)
GNL_OGJ	=	$(GNL_SRC:.c=.o)

INCLUDE	=	./include

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) -I $(MLX_DIR) $(OBJ) -L $(MLX_DIR) $(FLAGS) -o $@

clean	:
	$(RM) $(OBJ) $(GNL_OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

valgrind	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/sample1.ber

.PHONY	:	all clean fclean re