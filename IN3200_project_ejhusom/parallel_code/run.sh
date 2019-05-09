#!/bin/bash
make
for rank in {1..12}
do 
    for i in {1..5} 
    do
        mpirun -np $rank parallel_main.exe mona_lisa_noisy.jpg
        sleep 6s
    done
done

echo done

