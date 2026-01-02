obj-m := mkvm.o

mkvm-objs := src/main.o src/yelp.o

ccflags-y := -I$(src)/includ

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

