##
## AmauryDanisCousandier PROJECT, 2021
## RaspFanCtrl [WSL: Ubuntu]
## File description:
## Makefile
##

SRC	=	src/main.c

BINARY	=	RaspFanCtrl

build:
	gcc -o $(BINARY) $(src) -l -bcm2835

exec:
	sudo ./RaspFanCtrl &