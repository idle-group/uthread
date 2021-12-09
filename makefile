BUILD_DIR = ./build
AS = nasm
CC = gcc
LD = ld
LIB = -I lib/ -I /
ASFLAGS = -f elf32
CFLAGS = -m32 -Wall $(LIB) -c -std=gnu11 -fno-builtin -W -Wstrict-prototypes \
         -Wmissing-prototypes 
LDFLAGS =  -m32
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/uthread.o $(BUILD_DIR)/string.o $(BUILD_DIR)/list.o   $(BUILD_DIR)/switch.o

#编译c 代码

$(BUILD_DIR)/list.o: lib/list.c lib/global.h lib/list.h 
	$(CC) $(CFLAGS) $< -o $@
$(BUILD_DIR)/string.o: lib/string.c lib/global.h lib/string.h 
	$(CC) $(CFLAGS) $< -o $@
$(BUILD_DIR)/uthread.o: uthread.c uthread.h lib/string.h lib/global.h lib/list.h
	$(CC) $(CFLAGS) $< -o $@
$(BUILD_DIR)/main.o: main.c uthread.h uthread.c lib/string.h lib/global.h lib/list.h 
	$(CC) $(CFLAGS) $< -o $@
#编译汇编代码
$(BUILD_DIR)/switch.o: switch_to.S
	$(AS) $(ASFLAGS) $< -o $@
$(BUILD_DIR)/demo: $(OBJS)
	gcc  $(LDFLAGS) $^  -o $@

ALL: $(OBJS) $(BUILD_DIR)/demo
