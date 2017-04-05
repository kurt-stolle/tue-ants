#/bin/bash

echo "###########################################################"
cd src &&
echo "Compiling ants library"
gcc -Wextra -Og -c -g -o cell.o cell.c &&
gcc -Wextra -Og -c -g -o command.o command.c &&
gcc -Wextra -Og -c -g -o init.o init.c &&
gcc -Wextra -Og -c -g -o map.o map.c &&
gcc -Wextra -Og -c -g -o play.o play.c &&
gcc -Wextra -Og -c -g -o vector.o vector.c&&
gcc -Wextra -Og -c -g -o world.o world.c &&
gcc -Wextra -Og -c -g -o ants.o ants.c &&
echo "Generating libants.a"
ar rcs libants.a ants.o world.o vector.o play.o map.o init.o command.o cell.o &&
echo "Compiling main.o"
cc -Wextra -Og -c -g -o main.o main.c &&
echo "Linking bot program"
cc -Wextra -Og -g main.o -static -L. -lants -o ../bin/ants.bot -lm &&
echo "Done"
echo "###########################################################"