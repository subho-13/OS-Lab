#!/bin/bash

if test $# -eq 0
then
    startdir="$HOME"
else
    startdir="$1"
fi

count=0
for f in "$startdir"/*
do
    if test -d "$f"
    then
        bash "$0" "$f"
    else
        count=$(("$count" + 1))
    fi
done

echo "$startdir" "$count"