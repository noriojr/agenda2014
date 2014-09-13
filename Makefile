CC=gcc
LIBS=-L/usr/lib `pkg-config --libs gtk+-2.0`
INC=-I. -I./src -I/usr/include `pkg-config --cflags gtk+-2.0`
arqs=src/main.c src/agenda.c
arqh=src/agenda.h
objs=main.o agenda.o
prg=PCI-Agenda-2014
version=1.0.0

all: $(prg)

$(prg): .o
	$(CC) -g -o $@ $(objs) $(LIBS)

.o: clean
	$(CC) -g -c $(arqs) $(INC) 

clean:
	rm -rf $(objs) $(prg) 

dist:
	mkdir -p $(prg)-$(version)
	cp -rf docs src img Makefile PCI-Agenda-2014.anjuta $(prg)-$(version)
	tar -cvf $(prg)-$(version).tar.gz -z $(prg)-$(version) 
	rm -rf $(prg)-$(version) 
	