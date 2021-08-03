NAME	=	so_long

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

MLX_GIT	=	https://github.com/42Paris/minilibx-linux.git
FLAGS	=	-lmlx -lXext -lX11
MLX_DIR	=	../mlx-linux/
GNL_DIR	=	../get_next_line/

GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c

SRC		=	main_bonus.c read_map_bonus.c put_bonus.c init_vars_bonus.c \
			destroy_and_exit_bonus.c key_hook_bonus.c check_map_bonus.c \
			ft_itoa.c ft_strjoin.c put_step_to_window_bonus.c \
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
	cp $(NAME) ../

clean	:
	$(RM) $(OBJ)

fclean	:
	$(RM) $(NAME) $(OBJ)

re		:	fclean all

.PHONY	:	all clean fclean re