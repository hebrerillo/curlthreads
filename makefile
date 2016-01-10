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

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

main: $(OBJECTS)
	$(CC) -o main  $(OBJECTS) $(LFLAGS)

clean:
	rm *.o
	rm main