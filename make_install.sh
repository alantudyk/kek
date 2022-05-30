#!/bin/sh

gcc -O3 -flto -s kek.c -o kek &&
sudo mv kek /bin/kek
