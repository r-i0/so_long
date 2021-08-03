NAME	=	so_long
B_NAME	=	so_long_bonus

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

SRC_DIR	=	./src/
B_DIR	=	./bonus_src/
GNL_DIR	=	./get_next_line/

ifeq ($(shell uname), Darwin)
	MLX_GIT	=	https://github.com/dannywillems/minilibx-mac-osx.git
	FLAGS	=	-lmlx -framework OpenGL -framework AppKit
	MLX_DIR	=	./mlx-mac/
else
	MLX_GIT	=	https://github.com/42Paris/minilibx-linux.git
	FLAGS	=	-lmlx -lXext -lX11
	MLX_DIR	=	./mlx-linux/
endif

GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
SRC		=	$(SRC_DIR)main.c $(SRC_DIR)read_map.c $(SRC_DIR)put.c $(SRC_DIR)init_vars.c \
			$(SRC_DIR)destroy_and_exit.c $(SRC_DIR)loop_draw.c $(SRC_DIR)key_hook.c $(SRC_DIR)check_map.c \
			$(GNL_SRC)

OBJ		=	$(SRC:.c=.o)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(MLX_DIR)	:
	git clone $(MLX_GIT) $(MLX_DIR)

$(NAME)	:	$(MLX_DIR) $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -I $(MLX_DIR) $(OBJ) -L $(MLX_DIR) $(FLAGS) -o $@

clean	:
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(B_DIR) clean
	$(RM) $(OBJ)

fclean	:
	$(RM) $(MLX_DIR)
	$(MAKE) -C $(B_DIR) fclean
	$(RM) $(NAME) $(B_NAME) $(OBJ)

re		:	fclean all

bonus	:	$(B_DIR)
	$(MAKE) -C $(B_DIR)

valgrind	:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARG)
#make valgrind ARG=./maps/sample1.ber

.PHONY	:	all clean fclean re valgrind bonus