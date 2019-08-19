#!/bin/bash
make
for rank in {1..12}
do 
    for i in {1..4} 
    do
        mpirun -np $rank parallel_main.exe large.jpg
        sleep 3s
    done
done

echo done

