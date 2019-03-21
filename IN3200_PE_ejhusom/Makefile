# =============================================
# Title:           MAKEFILE
# Author:          Erik Johannes B. L. G. Husom
# Date:            2019-02-06
# Version:         0.2
# =============================================
EXEC 			= a.out
CC 		    	= gcc
FLAGS       	= -g -Wall -fopenmp

SRC 			:= $(wildcard *.c)
#====================================================
$(EXEC): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $@
	@echo "Linking complete!"
	@echo $(EXEC) "ready to run!"

clean:
	@rm -rf *.o $(EXEC)
	@echo "Cleanup complete!"

