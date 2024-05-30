CC			= gcc
CFLAGS		= -I include/ -Wall -std=c11
OBJFLAGS	= -nostdlib -nodefaultlibs -ffreestanding
BINARY		= endianConv
SRC_DIR		= src
OBJ_DIR		= obj

.PHONY: build release debug clean

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)	#Get all .c files from src/
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)	#Abstract all .c files to .o files


all: build | $(OBJ_FILES) $(BINARY)

gdb: $(BINARY)
	gdb $(BINARY)

release: CFLAGS += -O3 -s -static
release: build | $(BINARY)

debug: CFLAGS += -O0 -ggdb -D DEBUG
debug: build | $(BINARY)

$(BINARY): $(OBJ_FILES)									# binary <: objs
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(BINARY)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c							# forall .c -> build .o
	$(CC) $(CFLAGS) $(OBJFLAGS) -c $< -o $@

#yes, I am doing this on windows and yes. I hate this.
build:
	if not exist "$(OBJ_DIR)" mkdir $(OBJ_DIR)

clean:
	if exist "$(OBJ_DIR)/" del $(OBJ_DIR)\*.o
	if exist "$(OBJ_DIR)/" rmdir $(OBJ_DIR) > nul
	if exist "$(BINARY).exe" del $(BINARY).exe