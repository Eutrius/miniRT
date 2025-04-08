NAME 		= miniRT

CFLAGS 		= -Wall -Wextra -Werror -I./include
CC 			= cc
RM 			= rm -rf

SRC_DIR 	= src
OBJ_DIR 	= obj

LIBFT_DIR 	= lib/libft
LIBFT 		= $(LIBFT_DIR)/libft.a
MLX_DIR		= lib/mlx
MLX			= $(MLX_DIR)/libmlx.a
LIBS 		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -g

SRC = src/main.c \
	  src/hooks.c \
	  src/constructor.c \
	  src/math.c \
	  src/math2.c \
	  src/hit/hitplane.c \
	  src/hit/hitsphere.c \
	  src/hit/hitcylinder.c \
	  src/hit/hitcone.c \
	  src/checkerboard/checkerboard_pl.c \
	  src/checkerboard/checkerboard_sp.c \
	  src/checkerboard/checkerboard_cy.c \
	  src/checkerboard/checkerboard_co.c \
	  src/checkerboard/utils.c \
	  src/validate.c \
	  src/translate.c \
	  src/transform.c \
	  src/rotate.c \
	  src/cameraman.c \
	  src/unmarsh_utils.c \
	  src/unmarsh.c \
	  src/unmarsh_object.c \
	  src/memory_man.c \
	  src/debug.c \
	  src/render.c \
	  src/mlx.c \
	  src/lightman.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "Compiling miniRT..."
	@$(CC) $(OBJ) $(LIBS) -o $@
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -s -C $(LIBFT_DIR)
	@make bonus -s -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling MLX..."
	@make -s -C $(MLX_DIR)

clean:
	@echo "Cleaning..."
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MLX_DIR)
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning..."
	@$(RM) $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re
