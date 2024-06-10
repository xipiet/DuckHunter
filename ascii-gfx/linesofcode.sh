#!/bin/bash
echo -n "lines of code: "
find . -type d -name CMakeFiles -prune -o \( -name \*.h -o -name \*.cpp \) -exec cat {} \; | wc -l
