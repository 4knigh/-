
IE := main
SE := truncate.c
QU := truncate.o


$(IE): $(QU)
	$(CC) -o $@ $^

$(QU): $(SE)
	$(CC) -c $@ $^ -o $(QU)

clean:
	rm $(QU) -rf
	rm $(IE) -rf

install:
	cp $(IE) ..