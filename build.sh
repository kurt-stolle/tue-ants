#/bin/bash

echo "###########################################################"
cd src &&
echo "Compiling ants.o"
gcc -Wextra -Og -c -g -o ants.o cell.c command.c game.c init.c map.c play.c vector.c world.c &&
echo "Generating libants.a"
ar rcs libants.a ants.o &&
echo "Compiling main.o"
cc -Wextra -Og -c -g -o main.o main.c &&
echo "Linking bot program"
cc -Wextra -Og -g main.o -static -L. -lants -o ../bin/ants.bot -lm &&
echo "Done"
echo "###########################################################"