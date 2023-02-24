
LIBDIR			= libft
LIB				= $(LIBDIR)/libft.a
MLXDIR			= mlx
MLXLIB			= $(MLXDIR)/libmlx42.a
MLX_INCLUDEDIR	= $(MLXDIR)/include/MLX42
INCLUDE_DIR		= inc

SRC_DIR			= src
OBJ_DIR			= obj


SRCS_LIST		= fdf.c draw_line.c parse.c debug.c util.c matrix_utils.c matrix_inverse.c matrix_transformations.c \
				  draw_functions.c point_utils.c color.c world_transformations.c camera_transformations.c fdf_utils.c \
				  color_scheme_utils.c hooks_key_scroll_resize.c chrome.c hooks_frame_mouse.c
SRCS			= $(addprefix $(SRC_DIR)/, $(SRCS_LIST))
OBJS			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME			= fdf

CC				= gcc
CCFLAGS			= #-fsanitize=address # -Wall -Werror -Wextra
MLXFLAGS		= -framework Cocoa -framework IOKit -framework OpenGL -lglfw

RM				= rm -rf

all				: $(NAME)

$(NAME)			: $(LIB) $(MLXLIB) $(OBJS)
				@$(CC) $(CCFLAGS) $(MLXFLAGS) $(OBJS) $(MLXLIB) $(LIB) -o $(NAME)
				@echo FDF made.

$(OBJ_DIR)/%.o 	: $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@echo Creating fdf object: $@ "\x1b[1A\x1b[M"
				@$(CC) $(CCFLAGS) -I $(MLX_INCLUDEDIR) -I $(LIBDIR) -I $(INCLUDE_DIR) -c -o $@ $<

$(LIB)			:
				@$(MAKE) -C $(LIBDIR)

$(MLXLIB)		:
				@$(MAKE) -C $(MLXDIR)

clean			:
				@echo Cleaning fdf objects
				@$(RM) $(OBJ_DIR)
				@$(MAKE) -C $(LIBDIR) clean
				@$(MAKE) -C $(MLXDIR) clean

fclean			: clean
				@echo Cleaning fdf executable
				@$(RM) $(NAME)
				@$(MAKE) -C $(LIBDIR) fclean
				@$(MAKE) -C $(MLXDIR) clean

re				: fclean all

.PHONY 			: mlx clean fclean library
