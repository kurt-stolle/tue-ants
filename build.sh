#/bin/bash

echo "###########################################################"
cd src &&
echo "Compiling ants.c"
cc -Wall -Wextra -O -c -g -o ants.o ants.c &&
echo "Generating libants.a"
ar rcs libants.a ants.o &&
echo "Compiling main.c"
cc -Wall -Wextra -O -c -g -o main.o main.c &&
echo "Linking bot program"
cc -Wall -Wextra -O -g main.o -static -L. -lants -o ../bin/ants.bot -lm &&
echo "Done"
echo "###########################################################"