CC						:=			gcc
CFLAGS					:=		-fsanitize=address


NAME					:=			cube3D

UNAME_S					:= $(shell uname -s)
MLX_LINUX 				:= ../libs/mlx_linux
MLX						:= ../libs/liblmx
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

PARSING_FILES			:=			map_check.c			\
									map_open.c			\
									map_textures.c		\
									map_utils.c			\
									map_floor_ceiling.c	\

MAIN_FILE				:=			$(addprefix $(OBJS_PATH)/, $(MAIN_FILE:.c=.o))
PARSING_FILES			:=			$(addprefix $(OBJS_PATH)/parsing/, $(PARSING_FILES:.c=.o))

OBJS					:=			$(MAIN_FILE)				\
									$(PARSING_FILES)			\

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

##
$(NAME):	$(LIBFT) $(LIBPRINTF) $(OBJS)
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
			@rm -rf $(OBJS_PATH)

fclean:		clean
			@$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
			@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) fclean
			@echo "$(RED) rm libft.a libftprintf.a cube3D$(RESET)"
			@rm -f libft.a
			@rm -f libftprintf.a
			@rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re