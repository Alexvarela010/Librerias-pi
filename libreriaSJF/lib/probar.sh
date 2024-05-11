#!/bin/bash
gcc -c -g -I/usr/lib/jvm/java-17-openjdk-amd64/include -I/usr/lib/jvm/java-17-openjdk-amd64/include/linux -fPIC lib_Sjf.c
gcc -o lib_Sjf.so lib_Sjf.o -shared -fPIC
sudo cp lib_Sjf.so /usr/lib
sudo ldconfig
cd ..
javac aplicacion/*.java
java aplicacion.Aplicacion
