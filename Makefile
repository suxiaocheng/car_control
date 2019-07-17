INCPATH=
LIBSPATH=
LIBS=-lpthread -lmicrohttpd # -lwiringPi
CC=gcc
CFLAGS+=-g

SRC:=$(wildcard *.c)
OBJ := $(patsubst %.c,%.o,${SRC})

car_control:$(OBJ)
	$(CC) $^ -o $@ $(LIBSPATH) $(LIBS) $(INCPATH)

%.d:%.c
	${CC} -MM $< > $@ >$@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp

include $(SRC:.c=.d)


.PHONY: clean
clean:
	rm -rf *.o ${OBJ} %.d car_control *.tmp
