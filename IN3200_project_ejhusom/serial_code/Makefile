## =============================================
## Title:           MAKEFILE
## Date:            2019-04-17
## Version:         0.3
## =============================================
#EXEC 			= serial_code
#CC 		    	= gcc
#FLAGS       	= -g -Wall -O2
#LDFLAGS         = -L../simple-jpeg/ -lsimplejpeg
#
#SRC 			:= $(wildcard *.c)
#OBJS            := $(wildcard *.o)
##====================================================
#
#all: simple-jpeg $(EXEC)
#
#$(EXEC): $(OBJS)
#	$(CC) $(FLAGS) $< -o $@ $(LDFLAGS)
#	@echo "Linking complete!"
#	@echo $(EXEC) "ready to run!"
#
#simple-jpeg:
#	$(MAKE) -C ../simple-jpeg
#
#
#clean:
#	@rm -rf *.o $(EXEC)
#	$(MAKE) -C ../simple-jpeg clean
#	@echo "Cleanup complete!"

CC = gcc
CFLAGS = -O2
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

PROJ = serial_main
OBJS = serial_main.o

all: simple-jpeg $(PROJ)

serial_main: $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

obj-clean:
	$(RM) *.o

exec-clean:
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean:
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../simple-jpeg clean

