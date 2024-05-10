#!/bin/bash
gcc -c -g -I/usr/lib/jvm/java-17-openjdk-amd64/include -I/usr/lib/jvm/java-17-openjdk-amd64/include/linux -fPIC libio_Lineal.c
gcc -o libovaIO.so libio_Lineal.o -shared -fPIC
sudo cp libovaIO.so /usr/lib
sudo ldconfig
cd ..
javac aplicacion/*.java
java aplicacion.Aplicacion

