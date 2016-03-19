#!/bin/bash
<<COMMENT
To generate random 8-character passwords including alpha numeric characters

NOTE: <<In MAC>>
tr attempts to interpret its input as text in UTF-8 encoding. So it will complain and abort upon the first byte sequence which is not valid UTF-8.

Prefixing tr with LC_ALL=C or LC_CTYPE=C will export that variable into the environment of tr, thus changing its idea of the local character set to the C standard, i.e. everything is just a sequence of opaque bytes.


COMMENT

#In MAC
#
# METHOD 1
#random 8-character passwords including alpha numeric characters
cat /dev/urandom | LC_ALL=C tr -cd 'a-zA-Z0-9' | fold -w 8 | head -n 1

# METHOD 2
#advantage of being portable between OS X, Redhat, and Ubuntu.
#perl -pe 'tr/A-Za-z0-9//dc;' < /dev/urandom | head -c 8; echo


#In Ubuntu
#cat /dev/urandom | tr -cd 'a-zA-Z0-9' | fold -w 8 | head -n 1


#random 8-character passwords include everything {alpha-numeric, special }
#cat /dev/urandom | strings | head -n 1

