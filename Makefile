CC						:=			gcc
CFLAGS					:=			-fsanitize=address -g -fdiagnostics-color=always


NAME					:=			cube3D

UNAME_S					:= $(shell uname -s)
MLX_LINUX 				:= ./libs/mlx_linux
MLX						:= ./libs/libmlx
###													###
ifeq ($(UNAME_S), Linux)
	LINUX_MLX				:= -L$(MLX_LINUX) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
	LINK_FLAGS				:= $(LINUX_MLX)
endif

ifeq ($(UNAME_S), Darwin)
	MAC_MLX					:= -L$(MLX) -lmlx -framework OpenGL -framework AppKit
	LINK_FLAGS				:= $(MAC_MLX)
endif
###													###

SRCS_PATH				:=			srcs
OBJS_PATH				:=			objs
INCS_PATH				:=			-Iincludes


LIB_DIRECTORY			:=			./libs/
LIBFT					:=			$(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:=			$(LIB_DIRECTORY)libft/
LIBPRINTF				:=			$(LIBPRINTF_DIRECTORY)libftprintf.a
LIBPRINTF_DIRECTORY		:=			$(LIB_DIRECTORY)ftprintf/


MAIN_FILE				:=			main.c

PARSING_FILES			:=			map_open.c			\
									map_textures.c		\
									map_utils.c			\
									map_floor_ceiling.c	\
									map_helpers.c		\
									map_errors.c		\
									map_search.c		\
									map_parsing.c		\
									map_transform.c		\
									map_init_free.c		\


GRAPHICS_FILES			:=			draw_minimap.c\
									draw_shapes.c\
									draw_utils.c\
									render.c\


COMPUTE_FILES			:=			compute.c		\
									compute_init.c		\
									op_vectors.c		\
									op_vectors2.c		\

MYMINILIBX_FILES				:=	event_handler.c			\
									init_handler.c		\

DEBUG_FILES				:=			debug.c				\

MAIN_FILE				:=			$(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))
PARSING_FILES			:=			$(addprefix $(OBJS_PATH)/parsing/, $(PARSING_FILES:.c=.o))
GRAPHICS_FILES			:=			$(addprefix $(OBJS_PATH)/graphics/, $(GRAPHICS_FILES:.c=.o))
COMPUTE_FILES			:=			$(addprefix $(OBJS_PATH)/compute/, $(COMPUTE_FILES:.c=.o))
MYMINILIBX_FILES		:=			$(addprefix $(OBJS_PATH)/myminilibx/, $(MYMINILIBX_FILES:.c=.o))
DEBUG_FILES				:=			$(addprefix $(OBJS_PATH)/debug/, $(DEBUG_FILES:.c=.o))

OBJS					:=			$(MAIN_FILE)				\
									$(PARSING_FILES)			\
									$(GRAPHICS_FILES)			\
									$(COMPUTE_FILES)			\
									$(MYMINILIBX_FILES)				\
									$(DEBUG_FILES)				\

LIBS					:=			-L$(LIB_DIRECTORY) -lft -lftprintf

all:	$(NAME)

$(LIBFT):
	@echo "$(GREEN)Compilating Libft$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
	@cp libs/libft/libft.a .

$(LIBPRINTF):
	@echo "$(GREEN)Compilating Libprintf$(RESET)"
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
	@cp libs/ftprintf/libftprintf.a .

ifeq ($(UNAME_S), Linux)
mlx:
	@echo "$(GREEN)Compilating MlX$(RESET)"
	@$(MAKE) -sC $(MLX_LINUX)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
endif
ifeq ($(UNAME_S), Darwin)
mlx:
	@echo "$(GREEN)Compilating MLX$(RESET)"
	@$(MAKE) -sC $(MLX)
	@echo "$(CYAN)✔️  Compilation Done$(RESET)"
endif

##
$(NAME):	$(LIBFT) $(LIBPRINTF) $(OBJS) mlx
			@echo "$(GREEN)Compilating cube3D$(RESET)"
			@$(CC) $(CFLAGS) -Llibs/ftprintf -Llibs/libft -o $@ $(OBJS) $(LIBS) $(LINK_FLAGS)
			@echo "$(CYAN)✔️  Compilation Done$(RESET)"
##

tmp:
			@mkdir -p objs

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INCS_PATH) -c $< -o $@

clean:
	@echo "$(RED) Cleaning Directory /libs/libftprintf$(RESET)"
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	@echo "$(RED) Cleaning Directory /libs/libft$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@echo "$(RED) Cleaning Directory /objs$(RESET)"
ifeq ($(UNAME_S), Linux)
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -sC $(MLX_LINUX) clean
endif
ifeq ($(UNAME_S), Darwin)
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -sC $(MLX) clean
endif

fclean:		clean
			@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
			@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
			@echo "$(RED) rm libft.a libftprintf.a cube3D$(RESET)"
			@rm -rf libmlx.a
			@rm -f libft.a
			@rm -f libftprintf.a
			@rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re