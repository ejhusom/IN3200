# Makefile by Erik Johannes Husom on 2019-02-06
#==============================================
EXEC 			= parallel_main.exe
CC 		    	= mpicc
FLAGS       	= -Wall -g -O3
LDFLAGS         = -L../simple-jpeg/ -lsimplejpeg

SRC 			:= $(wildcard *.c)
#==============================================

all: simple-jpeg $(EXEC)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

$(EXEC): $(SRC)
	$(CC) $(FLAGS) $(SRC) -lm -o $@ $(LDFLAGS)
	@echo "Linking complete!"
	@echo $(EXEC) "ready to run!"

clean:
	@rm -rf *.o $(EXEC)
	$(MAKE) -C ../simple-jpeg clean
	@echo "Cleanup complete!"

