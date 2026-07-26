# Compiler and Flags
CC=gcc
CFLAGS= -Wall -Wextra -Iinclude  -std=c99

#Source files and Object files
SRC = src/main.c \
src/8088_Processor/cpu_struct.c \
src/8088_Processor/alu.c \
src/8088_Processor/control.c \
src/8088_Processor/interrupt.c \
src/8088_Processor/Biu.c \
src/memory/memory.c \
src/floppy/floppy.c  \
Tests/memory_test.c  \
Tests/Biu_test.c 

#Name of the Output executable
TARGET=happy_hours
#Defalult target:build the executable
all:$(TARGET)
$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o  $(TARGET) $(SRC)

#clean up build artifacts
clean:
	rm -f $(TARGET) 
.PHONY:all clean 