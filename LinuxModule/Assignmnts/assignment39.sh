#!/bin/bash
<<COMMENT
to search a user present in your system
COMMENT

username=$1
grep "^$1" /etc/passwd
