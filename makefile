#----- PROJECT NAME -----
NAME := pipex
BONUS_NAME := pipex_bonus
#----- DIRECTORIES -----
MANDATORY_DIR := mandatory
BONUS_DIR := bonus
INCDIR := inc
LIBDIR := lib
#----- SOURCE FILES -----
MANDATORY_FILES := $(addprefix $(MANDATORY_DIR)/, childs.c error.c free.c pipex.c)
BONUS_FILES := $(addprefix $(BONUS_DIR)/, childs_bonus.c cmd_bonus.c error_bonus.c free_bonus.c heredoc_bonus.c main_bonus.c paths_bonus.c pipex_bonus.c)
MANDATORY_OBJS := $(MANDATORY_FILES:%.c=%.o)
BONUS_OBJS := $(BONUS_FILES:%.c=%.o)
#----- LIBRARY FILES -----
LIBFTPRINTF := $(LIBDIR)/libftprintf.a
HEADERS := $(addprefix $(INCDIR)/, pipex.h pipex_bonus.h libft.h ft_printf.h get_next_line.h)
#----- COMPILER FLAGS -----
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR)
DEBUGFLAGS := -ggdb3 -D DEBUG=1
LDFLAGS := -L$(LIBDIR)
LDLIBS := -lftprintf
#----- COLORS -----
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
DEFAULT := \033[0m
#----- ----------- -----

all: $(NAME)

$(NAME): $(HEADERS) $(LIBFTPRINTF) $(MANDATORY_OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LDFLAGS) $(LDLIBS)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(HEADERS) $(LIBFTPRINTF) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LDFLAGS) $(LDLIBS)
	@echo -e "$(GREEN)$(BONUS_NAME) created!$(DEFAULT)"

%.o: %.c $(HEADERS) Makefile
	@${CC} ${CFLAGS} -c $< -o $@
	@echo -e "$(YELLOW)Compiled $< successfully!$(DEFAULT)"

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBDIR) all

clean:
	@$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)
	@$(MAKE) -C $(LIBDIR) clean
	@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo -e "$(RED)all deleted!$(DEFAULT)"

re: fclean all

debug: $(HEADERS) $(LIBFTPRINTF) $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(MANDATORY_OBJS) $(LDFLAGS) $(LDLIBS)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LDFLAGS) $(LDLIBS)

.PHONY: all clean fclean re debug bonus

