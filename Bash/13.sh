#!/bin/bash
output=$(du "$1" | grep -o "^[0-9]\+")
echo "Numbers of blocks occupied by $1 file = $output"
