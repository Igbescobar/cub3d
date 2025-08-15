NAME    = libft.a

SRCS    = ft_memset.c\
          ft_bzero.c\
          ft_memcpy.c\
          ft_memmove.c\
          ft_memchr.c\
          ft_memcmp.c\
          ft_strlen.c\
          ft_strlcpy.c\
          ft_strlcat.c\
          ft_strchr.c\
          ft_strrchr.c\
          ft_strnstr.c\
          ft_strncmp.c\
          ft_isalpha.c\
          ft_isdigit.c\
          ft_isalnum.c\
          ft_isascii.c\
          ft_isprint.c\
          ft_toupper.c\
          ft_atoi.c\
          ft_tolower.c\
          ft_calloc.c\
          ft_strdup.c\
          ft_substr.c\
          ft_strjoin.c\
          ft_strtrim.c\
        	ft_itoa.c\
          ft_split.c\
          ft_strmapi.c\
          ft_striteri.c\
          ft_putchar_fd.c\
          ft_putstr_fd.c\
          ft_putendl_fd.c\
          ft_putnbr_fd.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					

SRCS_BONUS = ft_lstnew.c\
						 ft_lstadd_front.c\
						 ft_lstsize.c\
						 ft_lstadd_back.c\
						 ft_lstiter.c\
						 ft_lstlast.c\
						 ft_lstmap.c\

OBJS    = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

BONUS_CACHE = .cache

LIBC    = ar rcs
CC      = cc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror

all: $(NAME)

bonus : $(BONUS_CACHE)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

$(BONUS_CACHE): $(OBJS_BONUS)
	$(LIBC) $(NAME) $(OBJS_BONUS)
	touch $(BONUS_CACHE)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
