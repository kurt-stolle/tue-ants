#/bin/bash

echo "###########################################################"
cd src &&
echo "Compiling ants library"
gcc -Wextra -Og -c -g -o ../lib/cell.o cell.c &&
gcc -Wextra -Og -c -g -o ../lib/command.o command.c &&
gcc -Wextra -Og -c -g -o ../lib/init.o init.c &&
gcc -Wextra -Og -c -g -o ../lib/map.o map.c &&
gcc -Wextra -Og -c -g -o ../lib/play.o play.c &&
gcc -Wextra -Og -c -g -o ../lib/vector.o vector.c&&
gcc -Wextra -Og -c -g -o ../lib/world.o world.c &&
echo "Generating libants.a"
cd ../lib
ar rcs libants.a world.o vector.o play.o map.o init.o command.o cell.o &&
echo "Compiling main.o"
cc -Wextra -Og -c -g -o main.o ../src/main.c &&
echo "Linking bot program"
cc -Wextra -Og -g main.o -static -L. -lants -o ../bin/ants.bot -lm &&
echo "Done"
echo "###########################################################"