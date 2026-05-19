obj-m += ldd.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# made:data.c
# 	cat data.c
# 	cat data.c > data.text
# 	cat data.text