CC      = gcc
CFLAGS  = -Wall -Wextra -g

TARGET   = program
PRELOAD  = preload.so
DYNLIB   = libdynfuncs.so

.PHONY: all run run_plain clean

all: $(TARGET) $(PRELOAD)

$(DYNLIB): dynfuncs.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

$(TARGET): main.c linkfuncs.c wrap.c $(DYNLIB)
	$(CC) $(CFLAGS) \
	    -Wl,--wrap,fred -Wl,--wrap,john \
	    -o $@ main.c linkfuncs.c wrap.c \
	    -L. -ldynfuncs -Wl,-rpath,.

$(PRELOAD): preload.c
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $< -ldl

run: all
	LD_PRELOAD=./$(PRELOAD) ./$(TARGET)

run_plain: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(PRELOAD) $(DYNLIB)
