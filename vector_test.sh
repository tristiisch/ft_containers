#!/bin/bash
# Script Linux & Mac pour lancer un main de tests, et vérifie si :
# - il n'y a pas de leaks dessus
# - si le programme return bien 0
# - [LINUX] Vérifie les invalid read/write et autre erreur invisible
# - Compare le resultat de la sortie standard avec la STL (le main doit gérer le #define IS_STL)

CC="clang++ -Wall -Wextra -std=c++98"
SRCS=srcs/test/vector_test.cpp
EXEC=vector_test.out

VALGRIND_FLAGS="--leak-check=full --error-exitcode=1 --show-leak-kinds=definite --track-origins=yes"
DIFF_VERSION=`diff --version | head -n 1 | sed 's/|/ /' | awk '{print $4}'`
if [ $(echo "$DIFF_VERSION >= 3.4" | bc -l) == 1 ]; then
	DIFF_FLAGS="--color"
else
	DIFF_FLAGS=""
fi

# Compile with our containers
$CC -D IS_STL=0 $SRCS -o ./$EXEC
if [ $? != 0 ]; then
	echo -e "\033[0;31mKO : compile error\033[0m"
	exit 1
fi

# Launch with our containers
./$EXEC | nl -w2 -s'	' > output
if [ $? != 0 ]; then
	cat output
	echo -e "\033[0;31mKO : prog not return 0\nError msg can be on top\033[0m"
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
	echo -e "\033[0;33mWARN: STL prog didn't compile\033[0m"
	exit 1
fi

# Launch with STL containers
./$EXEC\_STL | nl -w2 -s'	' > output_STL
if [ $? != 0 ]; then
	# cat output
	echo -e "\033[0;33mWARN: STL prog not return 0\033[0m"
# else
# 	cat output
fi
rm -f $EXEC\_STL

# Diff between STL containers and our containers
if [ "$(diff $DIFF_FLAGS output output_STL)" != "" ]; then
	echo -e "\033[0;31mKO : prog works not like STL\033[0m"
	diff $DIFF_FLAGS output output_STL
	rm -f output output_STL
	exit 1
else
	echo -e "\033[0;32mOK\033[0m"
fi
rm -f output output_STL
