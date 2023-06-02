# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeondle <hyeondle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 16:46:26 by hyeondle          #+#    #+#              #
#    Updated: 2023/06/02 20:40:31 by hyeondle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	miniRT

HEADER_DIR			=	./inc/
HEADERS				=	vector.h\
						object.h\
						map.h\
						trace.h
HEADER				=	$(addprefix $(HEADERS_DIR), $(HEADERS))

SOURCE_DIR			=	./src/
SOURCES_MAIN		=	main.c
SOURCES_VECTOR		=	vector.c\
						ray.c\
						basic_calculation.c\
						basic_calculation2.c\
						product_calculation.c
SOURCES_OBJECT		=	object.c\
						objects.c
SOURCES_MAP			=	map.c
SOURCES_TRACE		=	trace_ray.c\
						trace_object.c\
						trace_hit.c

SOURCE_MAIN			=	$(addprefix $(SOURCE_DIR), $(SOURCES_MAIN))
SOURCE_VECTOR		=	$(addprefix $(SOURCE_DIR)vector/, $(SOURCES_VECTOR))
SOURCE_OBJECT		=	$(addprefix $(SOURCE_DIR)object/, $(SOURCES_OBJECT))
SOURCE_MAP			=	$(addprefix $(SOURCE_DIR)map/, $(SOURCES_MAP))
SOURCE_TRACE		=	$(addprefix $(SOURCE_DIR)trace/, $(SOURCES_TRACE))

SOURCE				=	$(SOURCE_MAIN)\
						$(SOURCE_VECTOR)\
						$(SOURCE_OBJECT)\
						$(SOURCE_MAP)\
						$(SOURCE_TRACE)

SOURCE_DIRS			=	$(SOURCE_DIR)\
						$(SOURCE_DIR)vector/\
						$(SOURCE_DIR)object/\
						$(SOURCE_DIR)map/\
						$(SOURCE_DIR)trace/

OBJECTS				=	$(SOURCE:.c=.o)

#.INTERMEDIATE: $(OBJECTS)

CC					=	cc
RM					=	rm -f
RM_OBJECT			=	rm -rf $(OBJECT)

.c.o				:
						$(CC) -I$(HEADER_DIR) -c $< -o $(<:.c=.o)
#						mv $(<:.c=.o) $(OBJECT_DIR)


all	:	$(NAME)

$(NAME)	:	$(OBJECTS)
		$(CC) -I $(HEADER_DIR) $(OBJECTS) -o $(NAME)

clean	:
	rm -rf $(OBJECTS)
fclean	:	clean
	rm -rf $(NAME)

re	:
	make fclean
	make all

.PHONY	: all clean fclean re