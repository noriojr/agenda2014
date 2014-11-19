CC=gcc
LIBS=-L. -L/usr/lib `pkg-config --libs gtk+-2.0`
INC=-I. -I./src -I/usr/include `pkg-config --cflags gtk+-2.0`
arqs=src/main.c src/agenda.c
arqh=src/agenda.h src/icones.h
objs=main.o agenda.o
prg=PCI-Agenda-2014
version=1.0.0
ifeq ($(shell uname), Linux)
	RES=;
	LDLFAGS +=
	LDADD +=
else
	RES=.rc
	objs += win32.o
	LDFLAGS += -mwindows -D_WIN32_WINNT=0x0501
	LDADD += -lws2_32
endif

all: $(prg)

$(prg): .o $(RES)
	$(CC) $(LDFLAGS) -g -o $@ $(objs) $(LIBS) $(LDADD)

.o: clean
	$(CC) -g -c $(arqs) $(INC) 

.rc: 
	windres -DVERSION="\"$(version)\"" -o win32.o src/win32.rc

clean:
	rm -rf $(objs) $(prg) 

dist:
	mkdir -p $(prg)-$(version)
	cp -rf docs src img Makefile dados.csv PCI-Agenda-2014.anjuta $(prg)-$(version)
	tar -cvf $(prg)-$(version).tar.gz -z $(prg)-$(version) 
	rm -rf $(prg)-$(version) 
	