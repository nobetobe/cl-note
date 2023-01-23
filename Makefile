cc=gcc

all:
	$(MAKE) -C src/ cc=$(cc)

clean:
	rm note src/*.o
