#!/bin/bash
make
for i in {1..10}
do 
    ./serial_main.exe large.jpg
    sleep 2s
done

echo done
