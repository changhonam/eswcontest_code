CP_PATH=$(abspath ../..)/CrossCompiler
CROSS_COMPILE=$(CP_PATH)/gcc-linaro-arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

ARCH=arm
CC=$(CROSS_COMPILE)gcc
OBJ = controlSensor.o car_lib.c

OBJNAME = test
$(OBJNAME): $(OBJ)
	$(CC) -o $(OBJNAME) $(OBJ)
	scp $(OBJNAME) root@10.10.70.4:/home/root/

clean:
	rm -rf *.o $(OBJNAME)

