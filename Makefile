MLX42		=	mlx42
MLX42INC	=	$(MLX42)/include/MLX42.h
MLX42LIB	=	$(MLX42)/build/libmlx42.a
LIBFT		=	libft
LIBFTINC	=	$(LIBFT)/libft.h
LIBFTLIB	=	$(LIBFT)/libft.a
CC			=	cc
CCFLAG		=	-g  # -Wall -Werror -Wextra
LIBS		=	$(LIBFTLIB) $(MLX42LIB) -ldl -lglfw -pthread -lm
SRC			=	src/main.c src/color.c src/image.c src/camera.c \
				src/vector.c src/vector_two.c src/vector_three.c \
				src/range.c src/ray.c src/list.c src/light.c src/utils.c src/render.c \
				src/shape.c src/sphere.c src/plane.c src/cylinder.c  src/cylinder_utils.c \
				src/parsing.c src/parsing_func.c src/parsing_func_more.c src/init_shape.c
OBJ			=	$(SRC:.c=.o)
NAME		=	miniRT
INC			=	-Iinc -I$(MLX42INC) -I$(LIBFTINC)

all: $(LIBFTLIB) $(MLX42LIB) $(NAME)

mlx42clone:
	if [ ! -d "$(MLX42)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42); \
	fi

$(MLX42LIB): mlx42clone
	@cmake $(MLX42) -B $(MLX42)/build && make -C $(MLX42)/build -j4

$(LIBFTLIB):
	@$(MAKE) -C $(LIBFT) re

$(NAME): $(LIBFTLIB) mlx42 $(OBJ)
	$(CC) $(OBJ) $(CCFLAG) -o $(NAME) $(LIBS)

%.o: %.c
	@$(CC) $(CCFLAG) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX42)
	@$(MAKE) -C $(LIBFT) fclean

re:	fclean all

.PHONY: all clean fclean re