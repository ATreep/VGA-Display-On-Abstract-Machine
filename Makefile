NAME := hello
SRCS := hello.c
export ARCH := x86-qemu
export AM_HOME := path/to/abstract-machine
# export CROSS_COMPILE := x86_64-linux-musl-
export CROSS_COMPILE := x86_64-linux-gnu-

include $(AM_HOME)/Makefile

debug:
	qemu-system-i386 -s -S -machine accel=tcg -smp "1,sockets=1" \
		-drive format=raw,file=build/hello-x86-qemu &
	lldb -O "command script import debug.py"

log:
	make -nB \
	     | grep -ve '^\(\#\|echo\|mkdir\|make\)' \
	     | sed "s#$(AM_HOME)#\AM#g" \
	     | sed "s#$(PWD)#.#g" \
	     > compile.log
