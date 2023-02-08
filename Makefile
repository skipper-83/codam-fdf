
LIBDIR			= libft
LIB				= $(LIBDIR)/libft.a
MLXDIR			= mlx
MLXLIB			= $(MLXDIR)/libmlx42.a
MLX_INCLUDEDIR	= $(MLXDIR)/include/MLX42
INCLUDE_DIR		= inc

SRC_DIR			= src
OBJ_DIR			= obj


SRCS_LIST		= test.c draw_line.c
SRCS			= $(addprefix $(SRC_DIR)/, $(SRCS_LIST))
OBJS			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME			= fdf

CC				= cc
CCFLAGS			= #-Wall -Werror -Wextra
MLXFLAGS		= -lglfw

RM				= rm -rf

all				: $(NAME)

$(NAME)			: $(LIB) $(MLXLIB) $(OBJS)
				$(CC) $(CCFLAGS) $(MLXFLAGS) $(OBJS) $(MLXLIB) $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o 	: $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@echo Creating fdf object: $@ "\x1b[1A\x1b[M"
				$(CC) $(CCFLAGS) -I $(MLX_INCLUDEDIR) -I $(LIBDIR) -I $(INCLUDE_DIR) -c -o $@ $<

$(LIB)			:
				@$(MAKE) -C $(LIBDIR)

$(MLXLIB)		:
				git submodule init
				git submodule update
				$(shell cd mlx; cmake CMakeLists.txt)
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