#!/bin/bash
<<COMMENT
Using address range negation to print only the fifth line of 
/etc/passwd file. HInt: use delete editing command
COMMENT

sed -n '5'p /etc/passwd
