PSPDEV = $(shell psp-config --pspdev-path)
PSPBIN = $(PSPDEV)/bin

CC = psp-gcc
CPPFLAGS = -D_PSP_FW_VERSION=660
CFLAGS = -std=c89 -Wall -Wextra -pedantic
OBJS = psp_jmouse.o

all: $(OBJS)

psp_jmouse.o: psp_jmouse.c psp_jmouse.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
