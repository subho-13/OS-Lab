#!/bin/bash
printf "\t int \t printf  scanf \n"
for file in $@
do
    countInt=$(grep -o -w "int" $1 | wc -l)
    countPrintf=$(grep -o -w "printf" $1 | wc -l)
    countScanf=$(grep -o -w "scanf" $1 | wc -l)
    printf "$file\t $countInt \t $countPrintf \t $countScanf \n"
    # echo "In file $file"
    # echo "int occurs $countInt times"
    # echo "printf occurs $countPrintf times"
    # echo "scanf occurs $countScanf times"
done
