# ft_containers

`./test.sh` To start our tester
### How Work our tester
It will print the result of somes units tests with our vector, stack, map, then it compare the output with the STL ones. After that, it re-start with our and check for leaks (valgrind on linux, leaks on macos). If he find leaks, he try to find leaks on STL (maybe our tests with STL ?) and if it find it, a warning is printed.

`cd containers_test && ./do.sh vector stack map` To start mli42's tester
### Result on Linux :
<img align="center" src="containers_test_linux.png" />