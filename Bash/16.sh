#!/bin/sh

awk -v pattern="$1" -v replace="$2" '
    gsub(pattern, replace, $0)
' $3