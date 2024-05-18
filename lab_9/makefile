CC := g++
FLAGS := -no-pie

all: app.exe

app.exe: main.cpp
	$(CC) $^ $(FLAGS) -o $@


.PHONY: clean
clean:
	rm -rf *.exe *.out