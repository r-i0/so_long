NAME	=	so_long

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
FLAGS	=	-lmlx -lm -lXext -lX11
RM		=	rm -rf

SRC		=	test_put_image.c
OBJ		=	$(SRC:.c=.o)

INCLUDE	=	./include
MLX_DIR	=	./mlx-linux

.c.o	:
	$(CC) -c $< -o $(<:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) -I $(MLX_DIR) $(OBJ) -L $(MLX_DIR) $(FLAGS) -o $@