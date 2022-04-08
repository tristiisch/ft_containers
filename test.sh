#!/bin/bash
# Script Linux & Mac pour lancer un main de tests, et vérifie si :
# - il n'y a pas de leaks dessus
# - si le programme return bien 0 (pas de segfault ou sigabort)
# - [LINUX] Vérifie les invalid read/write et autre erreur invisible
# - Compare le resultat de la sortie standard avec la STL (le main doit gérer le #define IS_STL)

CC="c++ -Wall -Wextra -std=c++98"
EXEC_STL=test_stl
EXEC_FT=test_ft
MAX_NB_LINE=4

WORK=0
VALGRIND_FLAGS="--leak-check=full --error-exitcode=1 --show-leak-kinds=definite --track-origins=yes"
DIFF_VERSION=`diff --version | head -n 1 | sed 's/|/ /' | awk '{print $4}' | sed -e 's/\./000/g' -e 's/000/\./1'`
if [ $(echo "$DIFF_VERSION >= 3.4" | bc -l) == 1 ]; then
	DIFF_FLAGS="--color"
else
	DIFF_FLAGS=""
fi

if [[ $1 == "capacity" ]]; then
	PRECONCOMPIL_FLAGS+="-D CAPACITY_TEST"
fi

# Compile with our containers
function compile_our {
	make test_ft
	if [ $? != 0 ]; then
		echo -e "\033[0;31mKO : compile error\033[0m"
		exit 1
	fi
}

# Compile with STL containers
function compile_STL {
	make test_stl
	if [ $? != 0 ]; then
		echo -e "\033[0;33mWARN: STL prog didn't compile\033[0m"
		exit 1
	fi
}

# Launch with STL containers
function launch_STL {
	./$EXEC_STL | nl -w$MAX_NB_LINE -s'	' > output_STL
	PIPE=${PIPESTATUS[0]}
	if [ $PIPE == 139 ]; then
		echo -e "\033[0;33mWARN: STL prog Segmentation fault\033[0m"
	elif [ $PIPE != 0 ]; then
		echo -e "\033[0;33mWARN: STL prog return $PIPE\033[0m"
	fi
	rm -f $EXEC_STL
}

function KO_our {
	cat output
	echo -e "\033[0;31mKO : $*\033[0m"
	rm -f output $EXEC_FT
	compile_STL
	launch_STL
	exit 1
}

# Launch with our containers
function launch_our {
	./$EXEC_FT | nl -w$MAX_NB_LINE -s'	' > output
	PIPE=${PIPESTATUS[0]}
	if [ $PIPE == 139 ]; then
		KO_our "Segmentation fault"
	elif [ $PIPE != 0 ]; then
		KO_our "prog return $PIPE"
	else
		cat output
	fi
}

# Memory Check
function memory_check_STL {
	if command -v valgrind &>/dev/null ; then
		if ! valgrind $VALGRIND_FLAGS ./$EXEC_STL &>/dev/null ; then
			echo -e "\033[0;33mWARN STL : leaks --------------------------- valgrind result :\033[0m"
			valgrind $VALGRIND_FLAGS ./$EXEC_STL
			echo -e "\033[0;33mWARN STL : leaks or bad usage\033[0m"
		fi
	elif command -v leaks &>/dev/null ; then
		if ! leaks -atExit --q -- ./$EXEC_STL &>/dev/null ; then
			echo -e "\033[0;33mWARN STL : leaks --------------------------- leaks result :\033[0m"
			leaks -atExit --q -- ./$EXEC_STL
			echo -e "\033[0;33mWARN STL : leaks\033[0m"
		fi
	else
		echo -e "\033[0;33mWARN: can't do memory check, unable to find valgrind or leaks\033[0m"
	fi
	rm -f $EXEC_STL
}


# Memory Check
function memory_check {
	if command -v valgrind &>/dev/null ; then
		if ! valgrind $VALGRIND_FLAGS ./$EXEC_FT &>/dev/null ; then
			echo -e "\033[0;31mKO : leaks --------------------------- valgrind result :\033[0m"
			valgrind $VALGRIND_FLAGS ./$EXEC_FT
			echo -e "\033[0;31mKO : leaks or bad usage\033[0m"
			rm -f $EXEC_FT output
			compile_STL
			memory_check_STL
			WORK=1
		fi
	elif command -v leaks &>/dev/null ; then
		if ! leaks -atExit --q -- ./$EXEC_FT &>/dev/null ; then
			echo -e "\033[0;31mKO : leaks --------------------------- leaks result :\033[0m"
			leaks -atExit --q -- ./$EXEC_FT
			echo -e "\033[0;31mKO : leaks\033[0m"
			rm -f $EXEC_FT output
			WORK=1
		fi
	else
		echo -e "\033[0;33mWARN: can't do memory check, unable to find valgrind or leaks\033[0m"
	fi
}

# Diff between STL containers and our containers
function diff_our_STL {
	if [ "$(diff $DIFF_FLAGS output output_STL)" != "" ]; then
		echo -e "\033[0;31mKO : prog works not like STL\033[0m"
		diff $DIFF_FLAGS output output_STL
		rm -f output output_STL
		WORK=1
	else
		echo -e "\033[0;32mOK diff\033[0m"
	fi
}

compile_our
launch_our

compile_STL
launch_STL

diff_our_STL

rm -f output output_STL

memory_check

make clean

exit $WORK