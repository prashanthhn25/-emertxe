#!/bin/bash
<<COMMENT
To generate random 8-character passwords including alpha numeric characters
COMMENT

#random 8-character passwords including alpha numeric characters
cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 8 | head -n 1

#random 8-character passwords include everything {alpha-numeric, special }
#cat /dev/urandom | strings | head -n 1

