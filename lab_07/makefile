SRC_DIR := ./src
OBJ_DIR := ./out
INC_DIR := ./inc

OBJ_FILES := $(OBJ_DIR)/main.o $(OBJ_DIR)/strlenASM.o $(OBJ_DIR)/test.o $(OBJ_DIR)/strncpy.o

all: clean app.exe

app.exe: $(OBJ_FILES)
	g++ -I./$(INC_DIR) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p ./out
	g++ -I./$(INC_DIR) -masm=intel -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm
	mkdir -p ./out
	nasm -f elf64 $< -o $@

clean:
	rm -rf *.o *.exe ./out