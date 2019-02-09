#!/bin/bash

mkdir project
cd project
mkdir doc include src
touch include/func.h src/{func.c,main.c}
ls -R > contents.txt
cd ..
cp -r project projectV2
rm -r project
tar -cf pv2.tar projectV2
rm -r projectV2
