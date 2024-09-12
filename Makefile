MLX42		=	mlx42
MLX42INC	=	$(MLX42)/include/MLX42.h
MLX42LIB	=	$(MLX42)/build/libmlx42.a
LIBFT		=	libft
LIBFTINC	=	$(LIBFT)/libft.h
LIBFTLIB	=	$(LIBFT)/libft.a
CC			=	cc
CCFLAG		=	-g  # -Wall -Werror -Wextra
LIBS		=	$(LIBFTLIB) $(MLX42LIB) -ldl -lglfw -pthread -lm
SRC			=	src/main.c src/vector.c src/color.c src/image.c src/camera.c \
				src/range.c src/ray.c src/list.c \
				src/shape.c src/sphere.c src/plane.c src/cylinder.c  src/parsing.c \
				src/parsing_func.c
OBJ			=	$(SRC:.c=.o)
NAME		=	miniRT
INC			=	-Iinc -I$(MLX42INC) -I$(LIBFTINC)

all: libft mlx42 $(NAME)

mlx42clone:
	if [ ! -d "$(MLX42)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42); \
	fi

mlx42: mlx42clone
	@cmake $(MLX42) -B $(MLX42)/build && make -C $(MLX42)/build -j4

$(LIBFTLIB):
	$(MAKE) -C $(LIBFT)

$(NAME): $(LIBFTLIB) mlx42 $(OBJ)
	$(CC) $(OBJ) $(CCFLAG) -o $(NAME) $(LIBS)

%.o: %.c
	$(CC) $(CCFLAG) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX42)
	$(MAKE) -C $(LIBFT) fclean

re:	clean all

.PHONY: all clean fclean re