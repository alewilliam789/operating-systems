.DEFAULT_GOAL := default

CC?=gcc
CFLAGS?=-Wall -Werror -g3
SOURCES=main.c word_count.c
# comment the following out if you are providing your own sort_words
BINARIES=words
UNAME := $(shell uname -m)
LIBRARIES=wc_sort.o
ifeq "$(UNAME)" "aarch64"
	LIBRARIES:=wc_sort_arm.o
endif
ifeq "$(UNAME)" "arm64"
	LIBRARIES:=wc_sort_arm.o
endif

json: 
	bear -- make executable
	- rm a.out

%: %.c
	$(CC) $(CFLAGS) $(LIBRARIES) -o -g $@ $^

clean:
	rm -f $(BINARIES)

executable:
	$(CC) $(CFLAGS) $(SOURCES) $(LIBRARIES) -o $(BINARIES)

debug:
	gdb words
default: executable
