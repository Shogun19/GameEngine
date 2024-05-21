#!/bin/sh
bindir=$(pwd)
cd /home/shogun/GameEngine/Code/TP1/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "xYES" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		/usr/bin/gdb -batch -command=$bindir/gdbscript --return-child-result /home/shogun/GameEngine/Code/build/TP1 
	else
		"/home/shogun/GameEngine/Code/build/TP1"  
	fi
else
	"/home/shogun/GameEngine/Code/build/TP1"  
fi
