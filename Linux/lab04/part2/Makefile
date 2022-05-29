ifneq ($(KERNELRELEASE),)
	obj-m := md.o
else
	CURRENT = $(shell uname -r)
	KDIR = /lib/modules/$(CURRENT)/build
	PWD = $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

ins:
	@echo ">>>>> Loading md.ko..."
	insmod md.ko

rm:
	@echo ">>>>> Remove md.ko..."
	rmmod md

test: default ins write read rm

write:
	echo "message 1" > /proc/fortune
	echo "message 2" > /proc/fortune
	echo "message 3" > /proc/fortune

read:
	cat /proc/fortune
	cat /proc/fortune
	cat /proc/fortune

log:
	@dmesg -wH

clean:
	@rm -f *.o .*.cmd .*.flags *.mod *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions
disclean: clean
	@rm *.ko *.symvers
endif

# $(MAKE) - вызов MAKE в режиме ядра.