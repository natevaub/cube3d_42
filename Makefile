# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrouille <rrouille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 15:20:40 by rrouille          #+#    #+#              #
#    Updated: 2023/12/19 09:33:24 by rrouille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 CONFIGURATION                                #
# **************************************************************************** #

# Executable name
NAME = cub3D

# Directories
SRCSDIR = ${MODEDIR}/srcs
OBJSDIR = objs
LIBSDIR = ${MODEDIR}/libs
HDRDIR = ${MODEDIR}/includes
LIBFT = ${MODEDIR}/libs/libft
MLX = ${MODEDIR}/libs/mlx
BASICDIR = ./basic
BONUSDIR = ./bonus
EXTRABONUSDIR = ./extra_bonus
OBJS_FOLDERS = ${shell find ${SRCSDIR} -type d | sed "s|${SRCSDIR}|${OBJSDIR}|"}
MAKEFILE_UTILS = ./Makefile_utils

# Source and Object Files
SRCS			= ${shell find ${SRCSDIR} -type f -name '*.c'}
OBJS			= ${patsubst ${SRCSDIR}%,${OBJSDIR}%,${SRCS:%.c=%.o}}

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS_Linux = -L${MLX} -lmlx -L/usr/lib -lXext -lX11 -lm
LDFLAGS_Mac = -L${MLX} -lmlx -framework OpenGL -framework AppKit

# OS Specific Configuration
OS = ${shell uname}
ifeq (${OS},Linux)
    ECHO = echo -e
	MLX_ARCHIVE = ${MAKEFILE_UTILS}/archives/minilibx_mms_20200219_beta.tgz
    LDFLAGS = ${LDFLAGS_Linux}
else
    ECHO = echo
	MLX_ARCHIVE = ${MAKEFILE_UTILS}/archives/minilibx_opengl.tgz
    LDFLAGS = ${LDFLAGS_Mac}
endif

# Arguments passed to the executable
ARGS = ${filter-out $@, ${MAKECMDGOALS}}
PRINT_SCREEN = YES
FAST_MODE = NO
MODE = BASIC

ifeq (${MODE},BASIC)
	MODEDIR = ${BASICDIR}
else ifeq (${MODE},BONUS)
	MODEDIR = ${BONUSDIR}
else ifeq (${MODE},EXTRA_BONUS)
	MODEDIR = ${EXTRABONUSDIR}
endif

# Commands
RM				= rm -rf
MV				= mv
MKDIR			= mkdir -p
MAKE			= make -C
GIT				= git
DEBUG			= -fsanitize=address -g

# **************************************************************************** #
#                                 COLOR DEFINITIONS                            #
# **************************************************************************** #

# Colors for the terminal
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
ENDCOLOR = \033[0m

# Background colors
BG_G = \033[42m
BG_R = \033[41m
BG_Y = \033[43m
BG_B = \033[44m
BG_M = \033[45m
BG_C = \033[46m
BG_W = \033[47m

# Text formatting
BOLD = \033[1m
UNDERLINE = \033[4m
ITALIC = \033[3m
INVERTED = \033[7m

# Clear screen
CLEAR = \033c

# Clear line
CLEARLN = \r\033[K

# **************************************************************************** #
#                                  PROGRESS BAR                                #
# **************************************************************************** #

START			= ${ECHO} "${YELLOW}\n🚀 Start of program compilation 🚀\n${ENDCOLOR}"
END_COMP		= ${ECHO} "${GREEN}\n\n✅ Compilation completed successfully! ✅${ENDCOLOR}"
S_OBJS			= ${ECHO} "${RED}🧹 Cleaning objects... 🧹${ENDCOLOR}"
S_NAME			= ${ECHO} "${RED}🧹 Cleaning program... 🧹${ENDCOLOR}"
CHARG_LINE		= ${ECHO} "${BG_G} ${ENDCOLOR}\c"
BS_N			= ${ECHO} "\n"

# **************************************************************************** #
#                                 COMPILATION                                  #
# **************************************************************************** #

EXTRACT_MLX		= if [ ! -d "${MLX}" ]; then tar -xzf ${MLX_ARCHIVE} -C ${LIBSDIR} && ${MV} ${LIBSDIR}/minilibx* ${MLX}; fi
MAKE_LIB		= ${MAKE} ${MLX} > /dev/null 2>&1
CC_LIB			= ${CC} ${CFLAGS} ${OBJS} ${LIBFT}/objs/*/*.o ${LDFLAGS} -o ${NAME}
COMPILATION		= ${MAKE_LIB} && ${CC_LIB}

# **************************************************************************** #
#                                  COMMANDS                                    #
# **************************************************************************** #

all: draw_begining .WAIT extract_mlx .WAIT MODE=BASIC .WAIT ${NAME}

os:
			@${ECHO} "${OS}"

extract_mlx:
			@${ECHO} "${CLEAR}\c"
			@${MKDIR} -p ${LIBSDIR}
			@${EXTRACT_MLX}

# Build rule for object files
${OBJSDIR}/%.o : ${SRCSDIR}/%.c .WAIT lib
			@${MKDIR} ${OBJS_FOLDERS}
			@${CC} ${CFLAGS} -I ${HDRDIR} -c $< -o $@

# Linking rule
${NAME}: ${OBJS} .WAIT
			@${CHARG_LINE}
			${COMPILATION}
			${END_COMP}

# **************************************************************************** #
#                                   DRAWINGS                                   #
# **************************************************************************** #

draw_begining:
			@${ECHO} "${CLEAR}${GREEN}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/prog_name | while IFS= read -r line; do \
				printf '%s\n' "$$line"; \
				sleep 0; \
			done
			@sleep 0
			@${ECHO} "${CLEAR}"

draw_bonus:
			@${ECHO} "${CLEAR}${BLUE}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/bonus | \
				while IFS= read -r line; do \
					printf '%s\n' "$$line"; \
					sleep 0.01; \
				done; \
				printf '%s' "$$line"
			@sleep 0.3
			@${ECHO} "${ENDCOLOR}"

draw_ready:
			@${ECHO} "${CLEAR}${GREEN}${BOLD}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/prog_ready | \
				while IFS= read -r line; do \
					printf '%s\n' "$$line"; \
					sleep 0.01; \
				done; \
				printf '%s' "$$line"
			@sleep 0.3
			@${ECHO} "${ENDCOLOR}"
			@make help PRINT_SCREEN=NO

draw_run:
			@for i in 1 2 3; do \
				${ECHO} "${CLEAR}${BLUE}${BOLD}\c"; \
				cat "${MAKEFILE_UTILS}/ascii_art/prog_running_$$i"; \
				${ECHO} "${ENDCOLOR}"; \
				sleep 0.3; \
			done

draw_help:
			@${ECHO} "${GRAY}${BOLD}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/help_me | \
				while IFS= read -r line; do \
					printf '%s\n' "$$line"; \
				done; \
				printf '%s' "$$line"
			@${ECHO} "${ENDCOLOR}"

draw_norm_yes:
			@${ECHO} "${CLEAR}${GREEN}${BOLD}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/obama
			@${ECHO} "${ENDCOLOR}"

draw_norm_no:
			@${ECHO} "${CLEAR}${RED}${BOLD}\c"
			@cat ${MAKEFILE_UTILS}/ascii_art/obama_sad
			@${ECHO} "${ENDCOLOR}"

# **************************************************************************** #
#                                 UTILITIES                                    #
# **************************************************************************** #

lib:	clear
			@if [ "${FAST_MODE}" = "NO" ]; then \
				if [ -d ${LIBFT} ]; then \
					${ECHO} "${GREEN}🎉 Library already exists, updating it. 🔄\n${RESET}"; \
					git -C ${LIBFT} pull; \
					${ECHO} ""; \
					make -C ${LIBFT}; \
					${ECHO} "\c"; \
					sleep 0.3; \
				else \
					git clone https://github.com/rphlr/mylib --quiet ${LIBFT}; \
					make -C ${LIBFT}; \
					${ECHO} "\c"; \
					sleep 0.3; \
					${START}; \
				fi; \
			else \
				if [ -d ${LIBFT} ]; then \
					git -C ${LIBFT} pull; \
					make fast -C ${LIBFT}; \
				else \
					git clone https://github.com/rphlr/mylib --quiet ${LIBFT}; \
					make fast -C ${LIBFT}; \
				fi; \
			fi

help:
			@if [ "${PRINT_SCREEN}" = "YES" ]; then \
				${ECHO} "${CLEAR}\c"; \
				make draw_help; \
				for i in 3 2 1 0; do \
					printf '\r${BLUE}Help will be shown in: %d${ENDCOLOR}' "$$i"; \
					sleep 1; \
					printf '${CLEARLN}'; \
				done; \
			fi
			@${ECHO} "${GRAY}🏃 Run ${ITALIC}\`./${NAME}\`${ENDCOLOR}${GRAY} to see the program in action.${ENDCOLOR}${GRAY}"
			@${ECHO} "${BOLD}${UNDERLINE}💡 TIPS: 💡${ENDCOLOR}${GRAY}"
			@${ECHO} "\t- You can also use ${ITALIC}\`make run\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make r\`${ENDCOLOR}${GRAY} to try it out."
			@${ECHO} "\t- Check for memory leaks with ${ITALIC}\`make leaks\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make l\`${ENDCOLOR}${GRAY}."
			@${ECHO} "\t- Check the 42 norm with ${ITALIC}\`make norm\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make n\`${ENDCOLOR}${GRAY}."
			@${ECHO} "\t- Check the forbidden functions with ${ITALIC}\`make check_forbidden\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make cf\`${ENDCOLOR}${GRAY}."
			@${ECHO} "\t- Use ${ITALIC}\`make lldb\`${ENDCOLOR}${GRAY} to run the program with lldb."
			@${ECHO} "\t- Use ${ITALIC}\`make fast\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make cf\`${ENDCOLOR}${GRAY} to compile the program faster."
			@${ECHO} "\t- Use ${ITALIC}\`make clear\`${ENDCOLOR}${GRAY} or ${ITALIC}\`make c\`${ENDCOLOR}${GRAY} to clear the screen."
			@${ECHO} "\t- Use ${ITALIC}\`make clean\`${ENDCOLOR}${GRAY} to clean the object files."
			@${ECHO} "\t- Use ${ITALIC}\`make fclean\`${ENDCOLOR}${GRAY} to clean the object files and the executable."
			@${ECHO} ""
			@${ECHO} "${YELLOW}🌟 Use ${ITALIC}\`make help\`${ENDCOLOR}${YELLOW} or ${ITALIC}\`make h\`${ENDCOLOR}${YELLOW} to display these helpful tips. 🚀${ENDCOLOR}"
h:		help
 
# **************************************************************************** #
#                                RUN AND TESTS                                 #
# **************************************************************************** #

run:	clear fast
			@${ECHO} "${GREEN}🔧 Operations completed: 🔧${ENDCOLOR}"
			@./${NAME} ${ARGS}
r:		clear fast
			@${ECHO} "${GREEN}🔧 Operations completed: 🔧${ENDCOLOR}"
			@./${NAME} ${ARGS}

check_forbidden: clear fast
			@${ECHO} "${CLEAR}\c"
			@nm -u ${NAME} | grep -v '^_' | awk '!/^dyld_/' > ${MAKEFILE_UTILS}/functions_used
			sort ${MAKEFILE_UTILS}/functions_used -o ${MAKEFILE_UTILS}/functions_used_sorted
			sort ${MAKEFILE_UTILS}/authorized_functions -o ${MAKEFILE_UTILS}/authorized_functions_sorted
			${RM} ${MAKEFILE_UTILS}/functions_used ${MAKEFILE_UTILS}/authorized_functions
			${MV} ${MAKEFILE_UTILS}/functions_used_sorted ${MAKEFILE_UTILS}/functions_used
			${MV} ${MAKEFILE_UTILS}/authorized_functions_sorted ${MAKEFILE_UTILS}/authorized_functions
			comm -23 ${MAKEFILE_UTILS}/functions_used ${MAKEFILE_UTILS}/authorized_functions > ${MAKEFILE_UTILS}/unauthorized_used
			if [ -s ${MAKEFILE_UTILS}/unauthorized_used ]; then \
				${ECHO} "${RED}❌ The unauthorized functions used are:${ENDCOLOR}"; \
				cat ${MAKEFILE_UTILS}/unauthorized_used; \
				${ECHO} "${ENDCOLOR}"; \
			else \
				${ECHO} "${GREEN}✅ No unauthorized functions used! ✨${ENDCOLOR}"; \
			fi
			${RM} ${MAKEFILE_UTILS}/functions_used ${MAKEFILE_UTILS}/unauthorized_used
cf:		check_forbidden

# Fast compilation
fast: FAST_MODE := YES
fast: lib .WAIT extract_mlx .WAIT ${OBJS}	
		${COMPILATION}
f: fast

# Leaks check
leaks:	clear fast
			@${ECHO} "${CLEAR}\c"
			@leaks -atExit -- ./${NAME} ${ARGS}
l:		clear fast
			@${ECHO} "${CLEAR}\c"
			@leaks -atExit -- ./${NAME} ${ARGS}

# llbd
lldb:	clear fast
			@${ECHO} "${CLEAR}\c"
			@lldb ./${NAME} ${ARGS}
			@${ECHO} "${CLEAR}"

# Norminette check
norm:
			@norminette ${SRCSDIR} >/dev/null 2>&1 && norminette ${HDRDIR} >/dev/null 2>&1 && make draw_norm_yes || make draw_norm_no && norminette ${SRCSDIR} && norminette ${HDRDIR}
n:		norm

# **************************************************************************** #
#                                     GIT                                      #
# **************************************************************************** #

push: fclean
			@${ECHO} "${CLEAR}\c"
			@${GIT} add .
			@${ECHO} "${CYAN}✅ Added files to git! 📁"
			@if [ -z "${ARGS}" ]; then \
				${GIT} commit -m "💻 Auto-commit"; \
			else \
				${GIT} commit -m "${ARGS}"; \
			fi
			@${ECHO} "${BLUE}✅ Changes committed! ✔️"
			@git push
			@${ECHO} "${GREEN}✅ All changes are now on GitHub! 🚀${ENDCOLOR}"

pull:
			@${GIT} pull

# **************************************************************************** #
#                                   BONUS                                      #
# **************************************************************************** #

bonus: draw_bonus .WAIT extract_mlx .WAIT MODE=BONUS .WAIT ${NAME}
b:		bonus

extra_bonus: draw_bonus .WAIT extract_mlx .WAIT MODE=EXTRA_BONUS .WAIT ${NAME}
eb:		extra_bonus

# **************************************************************************** #
#                                   DUMMY                                      #
# **************************************************************************** #

# Dummy target to prevent arguments with dashes from being interpreted as targets
%:
			@:

# **************************************************************************** #
#                                   CLEANING                                   #
# **************************************************************************** #

clean:
			@${ECHO} "${CLEAR}\c"
			@${S_OBJS}
			@${RM} ${OBJSDIR} ${LIBSDIR}
			@${ECHO} "${CLEAR}\c"
			@${ECHO} "${GREEN}✅ Simple clean completed! ✨\n"

fclean: clean
			@${S_NAME}
			@${RM} ${NAME}
			@${ECHO} "${CLEAR}\c"
			@${ECHO} "${GREEN}✅ Deep clean completed! ✨"

re:		fclean .WAIT all

# **************************************************************************** #
#                                   PHONY TARGETS                              #
# **************************************************************************** #

.PHONY: all clean fclean re run test bonus help norm leaks lldb git clear cf