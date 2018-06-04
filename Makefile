# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtulchiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 18:49:17 by rtulchiy          #+#    #+#              #
#    Updated: 2018/06/03 21:18:44 by rtulchiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

OBJSRC = main.cpp VirtualMachine.cpp OperandFactory.cpp \

OBJC = $(OBJSRC:%.cpp=srcs/%.cpp)
OBJO = $(OBJSRC:.cpp=.o)
FLAGS = -Wall -Werror -Wextra -std=c++11

%.o: srcs/%.cpp
	clang++ $(FLAGS) -o $@ -c $< -I includes

all: $(NAME)

$(NAME): $(OBJO)
	clang++ $(FLAGS) -o $(NAME) $(OBJO)

clean:
	rm -f $(OBJO)

fclean: clean
	rm -f $(NAME)

re: fclean all
