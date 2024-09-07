MLX42		=	mlx42
MLX42INC	=	$(MLX42)/include/MLX42.h
MLX42LIB	=	$(MLX42)/build/libmlx42.a
LIBFT		=	libft
CC			=	cc
CCFLAG		=	-g  # -Wall -Werror -Wextra
LIBS		=	$(MLX42LIB) -ldl -lglfw -pthread -lm
SRC			=	src/main.c src/vector.c src/color.c src/image.c src/camera.c \
				src/range.c src/ray.c src/list.c \
				src/shape.c src/sphere.c src/plane.c src/cylinder.c  
OBJ			=	$(SRC:.c=.o)
NAME		=	miniRT
INC			=	-Iinc -I$(MLX42INC)

all: mlx42 libft $(NAME)

mlx42clone:
	if [ ! -d "$(MLX42)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42); \
	fi

mlx42: mlx42clone
	@cmake $(MLX42) -B $(MLX42)/build && make -C $(MLX42)/build -j4 \

libft:
	

$(NAME): mlx42 libft $(OBJ)
	$(CC) $(OBJ) $(CCFLAG) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CCFLAG) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX42)

re:	fclean all