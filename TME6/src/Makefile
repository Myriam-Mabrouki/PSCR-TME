CC=g++
FLAGS = -g3 -O0 -Wall -std=c++1y
EXECUTABLE = fork_exo combat

all: $(EXECUTABLE)

fork_exo : fork_exo.cpp
	$(CC) $(FLAGS) -o fork_exo fork_exo.cpp

combat: combat.cpp rsleep.cpp rsleep.h
	$(CC) $(FLAGS) -o combat combat.cpp rsleep.cpp rsleep.h
	
clean:
	rm -f $(OBJS) $(EXECUTABLE)
