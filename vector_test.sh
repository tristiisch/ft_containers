#!/bin/bash
# Script Linux & Mac pour lancer un main de tests, et vérifie si :
# - il n'y a pas de leaks dessus
# - si le programme return bien 0
# - [LINUX] Vérifie les invalid read/write et autre erreur invisible
# - Compare le resultat de la sortie standard avec la STL (le main doit gérer le #define IS_STL)

CC="clang++ -Wall -Wextra -std=c++98"
SRCS=vector_test.cpp
EXEC=vector_test.out

VALGRIND_FLAGS="--leak-check=full --error-exitcode=1 --show-leak-kinds=definite --track-origins=yes"

# Compile with our containers
$CC -D IS_STL=0 $SRCS -o ./$EXEC
if [ $? != 0 ]; then
	echo -e "\e[0;31mKO : compile error\e[0m"
	exit 1
fi

# Launch with our containers
./$EXEC > output
if [ $? != 0 ]; then
	cat output
	echo -e "\e[0;31mKO : prog not return 0\nError msg can be on top\e[0m"
	rm -f output $EXEC
	exit 1
else
	cat output
fi

# Memory Check
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

rm -f $EXEC

# Compile with STL containers
$CC -D IS_STL=1 $SRCS -o ./$EXEC\_STL 1>/dev/null 2>/dev/null
if [ $? != 0 ]; then
	echo -e "\e[0;33mWARN: STL prog didn't compile\e[0m"
	exit 1
fi

# Launch with STL containers
./$EXEC\_STL > output_STL
if [ $? != 0 ]; then
	# cat output
	echo -e "\e[0;33mWARN: STL prog not return 0\e[0m"
# else
# 	cat output
fi
rm -f $EXEC\_STL

# Diff between STL containers and our containers
if [ "$(diff output output_STL)" != "" ]; then
	echo -e "\e[0;31mKO : prog works not like STL\e[0m"
	diff output output_STL
	rm -f output output_STL
	exit 1
else
	echo -e "\033[0;32mOK\033[0m"
fi
rm -f output output_STL
