#!/bin/bash

./gen 500 T
./$1 a.bin b.bin out.bin 0 > cach_miss.txt
./cntrl cntrl.bin out.bin

./$1 a.bin b.bin out.bin 1 > cach_miss.txt
./cntrl cntrl.bin out.bin

./$1 a.bin b.bin out.bin 2 > cach_miss.txt
./cntrl cntrl.bin out.bin

./$1 a.bin b.bin out.bin 3 > cach_miss.txt
./cntrl cntrl.bin out.bin

./$1 a.bin b.bin out.bin 4 > cach_miss.txt
./cntrl cntrl.bin out.bin

./$1 a.bin b.bin out.bin 5 > cach_miss.txt
./cntrl cntrl.bin out.bin
