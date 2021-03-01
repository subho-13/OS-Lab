g++ driver.cpp -pthread -lrt -o driver

# Script to get data for analysis

echo "readers,writers,bsize,size,throughput,latency" > output.csv
for((readers = 5; readers < 8 ; readers++))
do
    writers=$((8 - $readers))

    for((size = 8192; size <= 65536; size = size*2))
    do
        for((bsize = $size; bsize*8192 >= size; bsize = bsize /2))
            do
                printf "%d,%d,%d,%d," $readers $writers $bsize $size >> output.csv
                timeout -s SIGINT 10s ./driver $readers $writers $bsize $size >> output.csv
            done
    done
done
