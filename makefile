DIRLIBRARY  = cddee
LIBRARIES = $(DIRLIBRARY)/liblist.so
LIBINCLUDE = -I$(DIRLIBRARY) -I/usr/include 

CDEBUG = -g
CC     = gcc
GCC    = gcc
CFLAGS = -Wall $(CDEBUG) $(LIBINCLUDE)
LFLAGS = -lcurl $(LIBRARIES) -pthread

SRCS_C = main.c curlthread.c
OBJECTS = $(SRCS_C:.c=.o)
	  
#VPATH = cddee

all: list main

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

list: 
	$(MAKE) -C $(DIRLIBRARY) list

main: $(OBJECTS)
	$(CC) -o main  $(OBJECTS) $(LFLAGS)

clean:
	rm *.o
	rm main
	$(MAKE) -C $(DIRLIBRARY) clean