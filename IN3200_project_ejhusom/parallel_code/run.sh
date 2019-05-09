#!/bin/bash
make
for rank in {2..6}
do 
    for i in {1..10} 
    do
        mpirun -np $rank parallel_main.exe mona_lisa_noisy.jpg
    done
done

echo done

