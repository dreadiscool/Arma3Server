rm arma-server
rm build/*
cp src/*.c build
cp src/headers/*.h build
gcc -g -lpthread -pthread build/main.c -o arma-server
./arma-server