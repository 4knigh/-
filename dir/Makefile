

IE := dir
SE := $(wildcard *.c)
QU := $(patsubst %.c, %.o, $(SE))

$(IE): $(QU)
	$(CC) -o $@ $^

clean:
	rm $(IE) -rf
	rm $(QU) -rf

install:
	mv $(IE) ..