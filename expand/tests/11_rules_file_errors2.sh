#!/bin/bash
"$1" tests/rules1.txt tests/BAD_RULES <<EOF
the program must terminate without printing this line.
EOF
# we are expecting the program to fail, so...
test "$!" != 0


    
