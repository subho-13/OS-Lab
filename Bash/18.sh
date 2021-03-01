#!/bin/sh

awk -F "$1" '
    {
        value = (NF?NF-1:0)
        if ( value != 0 ) { print NR, value }
        count += value
    }

    END {
        if (count == 0) { print "No match found" }
        else { print count }
    }
' $2