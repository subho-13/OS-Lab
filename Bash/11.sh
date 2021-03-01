#!/bin/bash

printf "Enter variable 1 :: "
read userv1
printf "Enter variable 2 :: "
read userv2

added=$(("$userv1" + "$userv2"))
echo "Adding 2 numbers :: $added"

multiplied=$(("$userv1" * "$userv2"))
echo "Multiplying 2 numbers :: $multiplied"

divided=$(("$userv1" / "$userv2"))
echo "Dividing 2 numbers :: $divided"

concatenated=$"$userv1 $userv2"
echo "Concatenating 2 numbers :: $concatenated"