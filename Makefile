NAME 		= miniRT
CFLAGS 		= -Wall -Wextra -Werror -I./include
CC 			= cc
SRC_DIR 	= src
OBJ_DIR 	= obj
LIBFT_DIR 	= lib/libft
MLX_DIR		= lib/mlx
LIBFT 		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LIBS 		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
RM 			= rm -rf

SRC = main.c constructor.c math.c hit.c validate.c unmarsh_utils.c unmarsh.c unmarsh_object.c memory_man.c debug.c render.c mlx.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJ)
	@echo "Compiling miniRT..."
	@$(CC) $(OBJ) $(LIBS) -o $@
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
