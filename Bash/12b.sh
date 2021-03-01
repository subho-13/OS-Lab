#!/bin/bash

echo "Files created on Year 2018"
find . -type f -newermt 2018-01-01 ! -newermt 2019-01-01 $1
echo "Files created on Year 2018"
find . -type f -newermt 2019-01-01 ! -newermt 2020-01-01 $1