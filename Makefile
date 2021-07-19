NAME	=	so_long

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
FLAGS	=	-lmlx -lm -lXext -lX11
RM		=	rm -rf

MLX_DIR	=	./mlx-linux/
GNL_DIR	=	./get_next_line/

SRC		=	main.c $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
GNL_SRC	=	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c
OBJ		=	$(SRC:.c=.o)
GNL_OGJ	=	$(GNL_SRC:.c=.o)

INCLUDE	=	./include

.c.o	:
	$(CC) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) -I $(MLX_DIR) $(OBJ) -L $(MLX_DIR) $(FLAGS) -o $@

clean	:
	$(RM) $(OBJ) $(GNL_OBJ)

fclean	:	clean
	$(RM) $(NAME)

re	:	fclean all