# how to:
# https://www.kernel.org/doc/html/latest/kbuild/makefiles.html

obj-m += communication.o
KDIR	:= /lib/modules/$(shell uname -r)/build

all: $(PWD)/Makefile
	make -C $(KDIR) M=$(PWD)/build src=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD)/build src=$(PWD) clean

clang:
	bear -- make CC=clang
