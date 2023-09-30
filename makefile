# Prepared by Abdelrahman Kamal ($(StudentDatabase))

CC = gcc
INCS = -I.
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
Project_name = StudentDatabase

all: $(Project_name).out
	@echo "--Build is Done--"

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

$(Project_name).out: $(OBJ) 
	$(CC) $(OBJ) -o $@ 


clean_all:
	rm *.o *.out

clean:
	rm *.out

