obj-m += ry_nb_pp.o
ry_nb_pp-objs = ryzen_nb_pp.o nb_smu_ops.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean