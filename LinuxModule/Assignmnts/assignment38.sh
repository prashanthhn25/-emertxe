#!/bin/bash
<<COMMENT
for each directory in the $PATH, display the number of executable files in that directory
COMMENT


find $PATH -executable | wc -l
