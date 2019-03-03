# =============================================
# Title:           MAKEFILE
# Author:          Erik Johannes B. L. G. Husom
# Date:            2019-02-06
# Version:         0.2
# =============================================
EXEC 			= week3.exe
CC 		    	= gcc
FLAGS       	= -Wall

SRC 			:= $(wildcard $*.c)
#====================================================
$(EXEC): $(SRC)
	@$(CC) $(FLAGS) -o $@
	@echo "Linking complete!"
	@echo $(EXEC) "ready to run!"

clean:
	@rm -rf *.o $(EXEC)
	@echo "Cleanup complete!"

