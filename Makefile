.PHONY: clean

all: build thread thread_shop

thread_shop: thread_shop.c
	gcc thread_shop.c -o thread_shop -lpthread

thread: thread.c
	gcc thread.c -o thread -lpthread

build:
	mkdir build

clean:
	rm -rf build main