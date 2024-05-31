CC			= gcc
CFLAGS		= -I include/ -Wall -std=c11
OBJFLAGS	= -nostdlib -nodefaultlibs -ffreestanding
BINARY		= endianConv
SRC_DIR		= src
OBJ_DIR		= obj

.PHONY: build release debug clean test

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
	del tests\*.out

test: build | $(OBJ_FILES) $(BINARY)
	$(BINARY).exe 16 tests/test_aligned.bin tests/aligned_16.out
	$(BINARY).exe 32 tests/test_aligned.bin tests/aligned_32.out
	$(BINARY).exe 64 tests/test_aligned.bin tests/aligned_64.out

	$(BINARY).exe 16 tests/test_unaligned.bin tests/unaligned_16.out
	$(BINARY).exe 32 tests/test_unaligned.bin tests/unaligned_32.out
	$(BINARY).exe 64 tests/test_unaligned.bin tests/unaligned_64.out