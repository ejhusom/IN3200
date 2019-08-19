#!/bin/bash
make
for i in {1..10}
do 
    ./serial_main.exe mona_lisa_noisy.jpg
    sleep 2s
done

echo done
