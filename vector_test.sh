#!/bin/bash
# Script Linux & Mac pour lancer un main de tests, et vérifie si :
# - il n'y a pas de leaks dessus
# - si le programme return bien 0
# - [LINUX] Vérifie les invalid read/write et autre erreur invisible

CC=clang++
SRCS=vector_test.cpp
EXEC=vector_test.out

VALGRIND_FLAGS= --leak-check=full --error-exitcode=1 --show-leak-kinds=definite --track-origins=yes

$CC $SRCS -o ./$EXEC
if [ $? != 0 ]; then
	echo -e "\e[0;31mKO : compile error\e[0m"
	exit 1
fi

if [[ $OSTYPE == 'darwin'* ]]; then

	if ! leaks -atExit --q -- ./$EXEC 1>/dev/null 2>/dev/null ; then
		echo -e "\033[0;31mKO : leaks\033[0m"
		leaks -atExit --q -- ./$EXEC
		rm -f $EXEC
		exit 1
	fi
else
	if ! valgrind $VALGRIND_FLAGS ./$EXEC 1>/dev/null 2>/dev/null ; then
		echo -e "\033[0;31mKO : leaks or bad usage\033[0m"
		valgrind $VALGRIND_FLAGS ./$EXEC
		rm -f $EXEC
		exit 1
	fi
fi
./$EXEC
if [ $? != 0 ]; then
	echo -e "\e[0;31mKO : prog not return 0\e[0m"
else
	echo -e "\033[0;32mOK\033[0m"
fi

rm -f $EXEC
