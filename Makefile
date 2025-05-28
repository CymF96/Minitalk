NAME = client
NAME2 = server
NAME3 = client_bonus
NAME4 = server_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra -std=gnu17
INC = -I include -I libft/include
LIBDIR = libft
LIBFT = $(LIBDIR)/libft.a
HEADER = minitalk.h
BHEADER = minitalk_bonus.h

CLIENTC = client.c
SERVERC = server.c
BCLIENTC = client_bonus.c
BSERVERC = server_bonus.c
CLIENTO = $(CLIENTC:.c=.o)
SERVERO = $(SERVERC:.c=.o)
BCLIENTO = $(BCLIENTC:.c=.o)
BSERVERO = $(BSERVERC:.c=.o)

all: $(NAME) $(NAME2)
bonus: $(NAME3) $(NAME4)

$(LIBFT):
	@$(MAKE) -C $(LIBDIR)

$(NAME): $(CLIENTO) $(HEADER) $(LIBFT)
	@$(CC) $(CFLAGS) $(CLIENTO) $(LIBFT) -o $(NAME)

$(NAME2): $(SERVERO) $(HEADER) $(LIBFT)
	@$(CC) $(CFLAGS) $(SERVERO) $(LIBFT) -o $(NAME2) 

$(NAME3): $(BCLIENTO) $(BHEADER) $(LIBFT)
	@$(CC) $(CFLAGS) $(BCLIENTO) $(LIBFT) -o $(NAME3)

$(NAME4): $(BSERVERO) $(BHEADER) $(LIBFT)
	@$(CC) $(CFLAGS) $(BSERVERO) $(LIBFT) -o $(NAME4) 

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBDIR) clean
	@rm -rf $(CLIENTO) $(SERVERO) $(BCLIENTO) $(BSERVERO)

fclean: clean
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -rf $(NAME) $(NAME2) $(NAME3) $(NAME4)

re: fclean all

.PHONY: all bonus clean fclean re