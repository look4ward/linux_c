set -e

gcc -Wall -g -c object.c -o object.o
gcc -Wall -g -c ex19.c -o ex19.o
gcc -Wall -g  object.o ex19.o main.c -o main 

./main
