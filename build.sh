gcc -o ./lib/dli.o -c ./src/dli.c -Iinclude -Wall &&
ar rcs ./lib/libdli.a ./lib/dli.o 
#&&
#gcc -fPIC -shared -o libdli.so dli.o
