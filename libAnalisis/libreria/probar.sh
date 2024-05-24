#!/bin/bash
gcc -c -g -I/usr/lib/jvm/java-17-openjdk-amd64/include -I/usr/lib/jvm/java-17-openjdk-amd64/include/linux -fPIC libreria_Taylor.c
gcc -o liblibreria_Taylor.so libreria_Taylor.o -shared -fPIC
sudo cp liblibreria_Taylor.so /usr/lib
sudo ldconfig
cd ..
javac aplicacion/*.java
java aplicacion.Aplicacion
