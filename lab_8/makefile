CC := g++
FLAGS := -m80387 -masm=intel -no-pie

all: task_1.exe task_2.exe task_3.exe

task_1.exe: task_1.cpp
	$(CC) $^ $(FLAGS) -o $@

task_2.exe: task_2.cpp
	$(CC) $^ $(FLAGS) -o $@

task_3.exe: task_3.cpp
	$(CC) $^ $(FLAGS) -o $@


.PHONY: clean
clean:
	rm -rf *.exe *.out
