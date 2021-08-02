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
B_SRC	=	$(B_DIR)main_bonus.c $(B_DIR)read_map_bonus.c $(B_DIR)put_bonus.c $(B_DIR)init_vars_bonus.c \
			$(B_DIR)destroy_and_exit_bonus.c $(B_DIR)key_hook_bonus.c $(B_DIR)check_map_bonus.c \
			$(B_DIR)ft_itoa.c $(B_DIR)ft_strjoin.c \
			$(GNL_SRC)

OBJ		=	$(SRC:.c=.o)
B_OBJ	=	$(B_SRC:.c=.o)
GNL_OGJ	=	$(GNL_SRC:.c=.o)

INCLUDE	=	./include

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
	$(RM) $(OBJ) $(B_OBJ)

fclean	:
	$(RM) $(MLX_DIR)
	$(RM) $(NAME) $(B_NAME) $(OBJ) $(B_OBJ)

re		:	fclean all

bonus	:	$(B_NAME)

$(B_NAME)	:	$(MLX_DIR) $(B_OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -I $(MLX_DIR) $(B_OBJ) -L $(MLX_DIR) $(FLAGS) -o $@

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