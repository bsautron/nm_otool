NAME = ft_nm

DEPENDENCIES_FOLDER = ../libraries
DEPENDENCIES = libft

SOURCES_FOLDER = .
SOURCES = 

OBJECTS_FOLDER = ../.objects/nm

INCLUDES_FOLDER = includes
INCLUDES = $(NAME).h

CC = gcc
CFLAGS = -Wextra -Wall -Werror

MAIN = main.c
MAIN_OBJECT = $(OBJECTS_FOLDER)/$(MAIN:.c=.o)

SOURCES_DEPENDENCIES = $(foreach dep,$(DEPENDENCIES),$(DEPENDENCIES_FOLDER)/$(dep)/$(dep).a)
INCLUDES_LIBRARIES_FOLDER = $(foreach dep,$(DEPENDENCIES),-I $(DEPENDENCIES_FOLDER)/$(dep)/includes)
MAKE_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make -C $(DEPENDENCIES_FOLDER)/$(dep);)
REBUILD_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make re -C $(DEPENDENCIES_FOLDER)/$(dep);)

OBJECTS = $(SOURCES:%.c=%.o)
OBJECTS_DESTINATION = $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))

all: init makelib $(NAME)

rebuild: fclean init rebuildlib $(NAME)

makelib:
	$(MAKE_LIBRARIES)

rebuildlib:
	$(REBUILD_LIBRARIES)

init:
	mkdir -p $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)

$(NAME): $(MAIN_OBJECT) $(OBJECTS_DESTINATION)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJECT) $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS)) $(SOURCES_DEPENDENCIES)

$(MAIN_OBJECT): $(MAIN) $(INCLUDES_FOLDER)/$(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) $(INCLUDES_LIBRARIES_FOLDER) -o $(MAIN_OBJECT) -c $(MAIN)

$(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, %.o): $(SOURCES_FOLDER)/%.c $(INCLUDES_FOLDER)/$(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) $(INCLUDES_LIBRARIES_FOLDER) -o $@ -c $<

clean:
	rm -f $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	rm -f $(MAIN_OBJECT)
	rm -rf $(OBJECTS_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all