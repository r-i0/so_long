NAME	=	so_long

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
FLAGS	=	-lmlx -lXext -lX11
RM		=	rm -rf

SRC_DIR	=	./src/
MLX_DIR	=	./mlx-linux/
GNL_DIR	=	./get_next_line/

SRC		=	$(SRC_DIR)main.c $(SRC_DIR)read_map.c $(SRC_DIR)put.c $(SRC_DIR)init_vars.c $(SRC_DIR)destroy_and_exit.c $(SRC_DIR)loop_draw.c $(SRC_DIR)key_hook.c $(SRC_DIR)check_map.c \
			$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
OBJ		=	$(SRC:.c=.o)
GNL_OGJ	=	$(GNL_SRC:.c=.o)

INCLUDE	=	./include

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(MLX_DIR)	:
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR)

$(NAME)	:	$(MLX_DIR) $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -I $(MLX_DIR) $(OBJ) -L $(MLX_DIR) $(FLAGS) -o $@

clean	:
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) $(OBJ) $(GNL_OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

valgrind1	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/sample1.ber
valgrind2	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/maltiple_map.ber
valgrind3	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/maltiple_player.ber
valgrind4	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/no_exit.ber
valgrind5	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/not_close1.ber
valgrind6	:
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all ./$(NAME) ./maps/not_rectangle.ber

.PHONY	:	all clean fclean re valgrind