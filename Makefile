# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agranger <agranger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/04 12:00:50 by agranger          #+#    #+#              #
#    Updated: 2023/02/19 06:01:57 by agranger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	miniRT

COMPILER		=	clang

CFLAGS			=	-Wall -Wextra -Werror -Wunreachable-code -MMD -Ofast

LIBDIR			=	libs

LIBFTDIR		=	$(LIBDIR)/libft

MLXDIR			=	$(LIBDIR)/minilibx-linux

SRCDIR			=	srcs

SRCBDIR			=	srcs_bonus

OBJDIR			=	objs

OBJBDIR			=	objs_bonus

HDIR			=	headers

CFILES			=	main.c \
					render.c \
					math/vector.c \
					math/math_tools.c \
					math/normal.c \
					mlx/mlx_tools.c \
					mlx/events.c \
					matrix/matrix.c \
					matrix/matrix_inverse.c \
					matrix/matrix_operations.c \
					matrix/matrix_scale_rotate.c \
					matrix/matrix_shear_transl.c \
					raytracing/rays.c \
					raytracing/intersection.c \
					raytracing/intersection_sphere.c \
					raytracing/intersection_plane.c \
					raytracing/intersection_cylinder.c \
					raytracing/reflection.c \
					raytracing/shadow.c \
					raytracing/color.c \
					parser/parser.c \
					parser/ambient.c \
					parser/error.c \
					parser/check_format.c \
					parser/camera.c \
					parser/light.c \
					parser/object.c \
					parser/sphere.c \
					parser/plane.c \
					parser/cylinder.c \
					parser/parsing_tools.c \
					parser/transform_matrix.c

CFILES_BONUS	=	$(CFILES) \
					raytracing/checkerboard.c \
					raytracing/intersection_cone.c \
					raytracing/bumpmap.c \
					parser/cone.c

MLX				=	$(MLXDIR)/libmlx.a

LIBFT			=	$(LIBFTDIR)/libft.a

LIBS			=	ft mlx Xext X11 m z

HEADERS			=	$(addprefix $(HDIR)/,$(HFILES))

SRCS			=	$(addprefix $(SRCDIR)/,$(CFILES))

SRCS_BONUS		=	$(addprefix $(SRCBDIR)/,$(CFILES_BONUS))

OBJS			=	$(addprefix $(OBJDIR)/,$(CFILES:%.c=%.o))

OBJS_BONUS		=	$(addprefix $(OBJBDIR)/,$(CFILES_BONUS:%.c=%.o))

DEP				=	$(OBJS:%.o=%.d)

DEP_BONUS		=	$(OBJS_BONUS:%.o=%.d)

LDFLAGS			=	-L$(LIBDIR)

LDLIBS			=	$(LIBS:%=-l%)

DEBUG			=	0

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

all							:	$(NAME)

$(NAME)						:	$(LIBFT) $(MLX) $(OBJS)
								@$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)						
								@echo "$(NAME) created"

bonus						:	$(LIBFT) $(MLX) $(OBJS_BONUS)
								@$(COMPILER) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)_bonus $(LDFLAGS) $(LDLIBS)						
								@echo "$(NAME)_bonus created"


-include $(DEP)
-include $(DEP_BONUS)

$(OBJDIR)/%.o   			:   $(SRCDIR)/%.c $(OBJDIR)/.DEBUG.$(DEBUG)
								@$(COMPILER) $(CFLAGS) $(HDIR:%=-I%) -c $< -o $@

$(OBJBDIR)/%.o   			:   $(SRCBDIR)/%.c $(OBJBDIR)/.DEBUG.$(DEBUG)
								@$(COMPILER) $(CFLAGS) $(HDIR:%=-I%) -c $< -o $@


$(OBJS)						:	| $(OBJDIR) 

$(OBJS_BONUS)				:	| $(OBJBDIR) 

$(OBJDIR)					:	
								@mkdir -p $@ \
									$@/matrix \
									$@/mlx \
									$@/math \
									$@/raytracing \
									$@/parser

$(OBJBDIR)					:	
								@mkdir -p $@ \
									$@/matrix \
									$@/mlx \
									$@/math \
									$@/raytracing \
									$@/parser

$(LIBFT)					:
								@$(MAKE) -sC $(LIBFTDIR)
								@cp $(LIBFT) $(LIBDIR)

$(MLX)						:
								@$(MAKE) -sC $(MLXDIR) > /dev/null 2>&1
								@cp $(MLX) $(LIBDIR)

clean           			:	 
								@$(MAKE) $@ -sC $(LIBFTDIR)
								@rm -rf $(MLXDIR)/obj
								@rm -rf $(OBJDIR) $(OBJBDIR) 
								@echo "object files removed"

fclean          			:   clean
								@$(MAKE) $@ -sC $(LIBFTDIR)
								@$(MAKE) $< -sC $(MLXDIR) > /dev/null 2>&1
								@rm -rf $(LIBDIR)/libft.a $(LIBDIR)/libmlx.a
								@rm -rf $(NAME) $(NAME)_bonus
								@echo "$(NAME) removed"

debug						:
								@$(MAKE) DEBUG=1 --no-print-directory
								@$(MAKE) bonus DEBUG=1 --no-print-directory

$(OBJDIR)/.DEBUG.$(DEBUG)	:	| $(OBJDIR)
								@rm -rf $(OBJDIR)/.DEBUG.*
								@touch $(OBJDIR)/.DEBUG.$(DEBUG)

$(OBJBDIR)/.DEBUG.$(DEBUG)	:	| $(OBJBDIR)
								@rm -rf $(OBJBDIR)/.DEBUG.*
								@touch $(OBJBDIR)/.DEBUG.$(DEBUG)

re							:   fclean all 

re_bonus					:   fclean bonus 

malloc_test					:	$(LIBFT) $(MLX) $(OBJS_BONUS)
								@$(COMPILER) $(CFLAGS) -g3 -fsanitize=undefined -rdynamic -o $@ $(OBJS_BONUS) $(LDFLAGS) $(LDLIBS) -L. -lmallocator						

.PHONY          			:   clean fclean re all
